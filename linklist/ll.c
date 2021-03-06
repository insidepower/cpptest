/*#########################################################################
  ##  FILENAME: ll.c
  ##
  ##  DESC: first-in first-out link-list
  ##  USAGE:
  ##  IMP NOTE:
  ##  COMPILATION:
  ##  gcc -D_GNU_SOURCE -c -g -o mem memDebug.c
  ##  gcc -g ll.h mem ll.c
  #########################################################################*/
/*==========================================================================
  ==  INCLUDES
  ==========================================================================*/
#include <stdio.h>
#include <pthread.h>
#include <assert.h>

#include "ll.h"
#include "global.h"
#include "memDebug.h"
/*============================================================================
  ==  MACRO CONSTANTS
  ============================================================================*/
/// maximum number of ll node can be stored in the queue
#define MAX_TOTAL_LL_NODE			(20)
/*==========================================================================
  ==  GLOBAL VARIABLES
  ==========================================================================*/
int llBox_cnt=1;
/// global mutex for init_ll
pthread_mutex_t gpMutex=PTHREAD_MUTEX_INITIALIZER;

/*++++++++++++++++++++++++++++< FUNCTION >++++++++++++++++++++++++++++++++*/
/*=========================================================================
  ==  @ init_ll @
  ==
  ==  DESC: init link-list with its own pHead, pTail, total count and mutex
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN: NULL if failure, else a new pointer 
  ==  IMP NOTE:
  =========================================================================*/
void init_ll(llBox ** p_pllBox, const char * strllBoxNm)
{
	pthread_mutex_lock(&gpMutex);
	//---------------------------------------------- init llBox's name//
	//char * str_name = (char *) MALLOC(MAX_FILE_NM_LEN, "str_name_init");
	///// LEAK-CHK: myllx of str_name must not exceed MAX_FILE_NM_LEN
	//sprintf(str_name, "myllBox%d", llBox_cnt++);
	//STR_LEN_CHECK(MAX_FILE_NM_LEN, strlen(str_name));
	//if(MAX_LL_INIT_CALL<=llBox_cnt){
	//	/// number of init() call exceed what program can handle
	//	PERROR("llBox_cnt==MAX_LL_INIT_CALL\n");
	//	FREE(str_name, "str_name_init");
	//	p_pllBox=NULL;
	//	goto exit_init_ll;
	//}
	STR_LEN_CHECK(MAX_FILE_NM_LEN, strlen(strllBoxNm));

	//------------------------------------------ init semaphore used by llBox//
	/// create semaphore for multiple writers/reader using this link-list
	sem_t * pSem_llBox = (sem_t *) MALLOC (sizeof(sem_t), "pSem_llBox");
	if(-1==sem_init(pSem_llBox, 0, 0)){
	//if(sem_init(&sem_llBox, 0, 0x80000000) < 0){
		//FREE(str_name, "str_name_init");
		p_pllBox=NULL;
		PERROR("semaphore init failed\n");
		perror("Err! semaphore init failed");
		goto exit_init_ll;
	}

	//------------------------------------------- init mutex used by llBox//
	pthread_mutex_t * pMutex=NULL;
	pMutex = (pthread_mutex_t *) MALLOC(sizeof(pthread_mutex_t), "llMutex");
	pthread_mutex_init(pMutex, NULL);
	//printf("szof pthread_mutex_t=%d\n", sizeof(pthread_mutex_t));


	//---------------------------------------------- init llBox//
	/// name to be used by all sub-node added to this llBox
	char * strNodeNm = (char *) MALLOC(MAX_FILE_NM_LEN, "nodeName");
	sprintf(strNodeNm, "%s_node", strllBoxNm);
	assert((MAX_FILE_NM_LEN-strlen(strNodeNm)) > 0 );
	STR_LEN_CHECK(MAX_FILE_NM_LEN, strlen(strNodeNm));

	llBox * pllBox = (llBox *) MALLOC(sizeof(llBox), strllBoxNm);
	pllBox->pMutex = pMutex;
	pllBox->pHead = NULL;
	pllBox->pTail = pllBox->pHead; //at start, pTail=pHead
	pllBox->pSem = pSem_llBox;
	pllBox->total = 0;
	pllBox->llBoxNm=strllBoxNm;
	pllBox->llBoxNodeNm=strNodeNm;

	*p_pllBox = pllBox;

exit_init_ll:
	pthread_mutex_unlock(&gpMutex);
}

/*=========================================================================
  ==  @ add_ll @
  ==
  ==  DESC: add node to the tail pllBox
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE: Ownership of pv is transferred from caller function to 	
  				add_ll upon calling add_ll, thus no further modification of
				pv is allowed beyond this point
  =========================================================================*/
int add_ll(OUT llBox * pllBox, OUT void **ppv)
{
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);
	int status = SOK_ADD_LL;

	/// check if total exceeded MAX_TOTAL_LL_NODE
	if(pllBox->total < MAX_TOTAL_LL_NODE){
		/// .no, added the node

		ll * pllnew = NULL;
		if(0==pllBox->total){
			/// link-list is empty
			assert(NULL==pllBox->pHead);
			assert(NULL==pllBox->pTail);
			pllnew = (ll *)MALLOC(sizeof(ll), pllBox->llBoxNodeNm);
			pllBox->pHead = pllnew;
			pllBox->pTail = pllBox->pHead;
		}else{
			pllnew = (ll *) MALLOC(sizeof(ll), pllBox->llBoxNodeNm);
			pllBox->pTail->pNext = pllnew;
			pllBox->pTail=pllnew;
		}

		pllnew->pNext=NULL;
		pllnew->pv=*ppv;
		*ppv=NULL;
		//*p_pll = pllnew;
		++pllBox->total;
		sem_post(pllBox->pSem);
		//status = SOK_ADD_LL;
	}else{
		/// .yes, discard msdu packet
		PRINT("pllBox->total(%d)>MAX_TOTAL_LL_NODE, discarded\n",pllBox->total);
		status = ERR_ADD_LL;
	}
	pthread_mutex_unlock(pllBox->pMutex);
	return status;
}

/*=========================================================================
  ==  @ rm_ll @
  ==
  ==  DESC: delete first node from pllBox 
  ==  USAGE:
  ==  INPUTS: 
  		p_pllBox : 
		pv : data pointer to return to caller function
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE: 
  ==     rm_ll() does not free pv/ struct pointed by pv
  =========================================================================*/
void rm_ll(OUT llBox * pllBox, void **pv)
{
	assert(NULL!=pllBox);
	pthread_mutex_lock((pllBox)->pMutex);

	assert(pllBox->total > 0);
	ll * pllToBeDel = pllBox->pHead;
	*pv = pllToBeDel->pv;

	pllBox->pHead = pllBox->pHead->pNext;
	--pllBox->total;

	if(0==pllBox->total){
		/// if last node, set tail to NULL
		assert(NULL==pllBox->pHead);
		pllBox->pTail=NULL;
	}

	/// LEAK-CHK:pv should be freed outside this function
	pllToBeDel->pNext=NULL;
	pllToBeDel->pv=NULL;
	FREE(pllToBeDel, pllBox->llBoxNodeNm);

	pthread_mutex_unlock(pllBox->pMutex);
}

/*=========================================================================
  ==  @ get_ll @
  ==
  ==  DESC: 
  == 	try to get one node from ll, if no node available, pend on 
  ==	semaphore
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE:
  =========================================================================*/
void get_ll(OUT llBox * pllBox, void **pv)
{
	sem_wait(pllBox->pSem);
	rm_ll(pllBox, pv);
}

/*============================================================================
  ==  @ get_ll_total @
  ==
  ==  DESC: return the total node in this llBox
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE:
  ============================================================================*/
void get_ll_total(const llBox * pllBox, int * pTotal)
{
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);
	*pTotal=pllBox->total;
	pthread_mutex_unlock(pllBox->pMutex);
}

/*=========================================================================
  ==  @ print_ll @
  ==
  ==  DESC: traverse through and print out the link-list
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE:
  =========================================================================*/
void print_ll(const llBox * pllBox, void (*pvPrint)(void * pv))
{
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);

	int count=pllBox->total;
	ll * pllTemp = pllBox->pHead;
	while(count--){
		assert(NULL!=pllTemp);
		printf("(%d):pllTemp->pv=%p\n", count, pllTemp->pv);
		if(NULL!=pvPrint){
			pvPrint(pllTemp->pv);
		}
		pllTemp=pllTemp->pNext;
	}
	assert(NULL==pllTemp);
	pthread_mutex_unlock(pllBox->pMutex);
}

/*=========================================================================
  ==  @ end_ll @
  ==
  ==  DESC: deleting the created llBox and all its remaining node
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE:
  =========================================================================*/
void end_ll(OUT llBox ** p_pllBox)
{
	pthread_mutex_lock((*p_pllBox)->pMutex);
	llBox * pllBox=*p_pllBox;
	char * str_name = NULL;
	pthread_mutex_t * pMutexTemp = pllBox->pMutex;
	str_name = (char *) MALLOC(strlen(pllBox->llBoxNm)+1, "boxToBeDelName");
	strcpy(str_name, pllBox->llBoxNm);

	//TODO: free remaining ll node

	/// freeing the semaphore used
	sem_destroy(pllBox->pSem);
	FREE(pllBox->pSem, "pSem_llBox");

	/// NOTE: pllBox->pMutex will be freed in the end, since still in used
	pllBox->pMutex=NULL;
	//FREE(pllBox->llBoxNm, "str_name_init");
	FREE(pllBox->llBoxNodeNm, "nodeName");
	pllBox->llBoxNm=NULL;
	FREE(pllBox, str_name);
	pllBox=NULL;

	FREE(str_name, "boxToBeDelName");
	str_name=NULL;
	pthread_mutex_unlock(pMutexTemp);

	/// freeing pllBox->pMutex
	/// INFO: mutex must be destroyed b4 free and reuse
	pthread_mutex_destroy(pMutexTemp);
	FREE(pMutexTemp, "llMutex");
	pMutexTemp=NULL;
}


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
#include "ll.h"
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
void init_ll(llBox ** p_pllBox)
{
	pthread_mutex_lock(&gpMutex);
	//---------------------------------------------- init llBox's name//
	/// IMP: myll_name should be freed when llBox is deleted
	char * str_name = (char *) MALLOC(MAX_FILE_NM_LEN, "str_name_init");
	/// LEAK-CHK: myllx of str_name must not exceed MAX_FILE_NM_LEN
	sprintf(str_name, "myll%d", llBox_cnt++);
	if(MAX_LL_INIT_CALL<=llBox_cnt){
		/// number of init() call exceed what program can handle
		PERROR("Err! llBox_cnt==MAX_LL_INIT_CALL\n");
		FREE(str_name, "myll_name");
		p_pllBox=NULL;
		goto exit_init_ll;
	}

	//------------------------------------------- init mutex used by llBox//
	pthread_mutex_t * pMutex=NULL;
	pMutex = (pthread_mutex_t *) MALLOC(sizeof(pthread_mutex_t), "llMutex");
	pthread_mutex_init(pMutex, NULL);
	printf("szof pthread_mutex_t=%d\n", sizeof(pthread_mutex_t));

	//---------------------------------------------- init llBox//
	llBox * pllBox = (llBox *) MALLOC(sizeof(llBox), str_name);
	pllBox->pMutex = pMutex;
	pllBox->pHead = NULL;
	pllBox->pTail = pllBox->pHead; //at start, pTail=pHead
	pllBox->total = 0;
	pllBox->llBoxNm=str_name;

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
  ==  IMP NOTE:
  =========================================================================*/
void add_ll(MODIF llBox ** p_pllBox, MODIF ll **p_pll)
{
	llBox * pllBox = *p_pllBox;
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);
	ll * pllnew = NULL;
	if(NULL==pllBox->pTail){
		/// link-list is empty
		assert(NULL==pllBox->pHead);
		assert(0==pllBox->total);
		pllnew = (ll *)MALLOC(sizeof(ll), pllBox->llBoxNm);
		pllBox->pHead = pllnew;
		pllBox->pTail = pllBox->pHead;
	}else{
		pllnew = (ll *) MALLOC(sizeof(ll), pllBox->llBoxNm);
		pllBox->pTail->pNext = pllnew;
	}

	pllnew->pNext=NULL;
	*p_pll = pllnew;
	++pllBox->total;
	pthread_mutex_unlock(pllBox->pMutex);
}

/*=========================================================================
  ==  @ rm_ll @
  ==
  ==  DESC: delete first node from pllBox 
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE: 
  ==     rm_ll() does not free pv/ struct pointed by pv
  =========================================================================*/
void rm_ll(MODIF llBox ** p_pllBox, void **pv)
{
	llBox * pllBox = *p_pllBox;
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);

	assert(pllBox->total > 0);
	ll * pllToBeDel = pllBox->pHead;
	*pv = pllToBeDel->pv;

	pllBox->pHead = pllBox->pHead->pNext;
	--pllBox->total;

	/// LEAK-CHK:pv should be freed outside this function
	pllToBeDel->pNext=NULL;
	pllToBeDel->pv=NULL;
	FREE(pllToBeDel, pllBox->llBoxNm);

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
void print_ll(CONST llBox * pllBox, void (*pvPrint)(void * pv))
{
	assert(NULL!=pllBox);
	pthread_mutex_lock(pllBox->pMutex);

	int count=pllBox->total;
	ll * pllTemp = pllBox->pHead;
	while(count--){
		assert(NULL!=pllTemp);
		printf("(%d):", count);
		pvPrint(pllTemp->pv);
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
void end_ll(MODIF llBox ** p_pllBox)
{
	llBox * pllBox=*p_pllBox;
	pthread_mutex_lock(pllBox->pMutex);
	char * str_name = NULL;
	pthread_mutex_t * pMutexTemp = pllBox->pMutex;
	str_name = (char *) MALLOC(strlen(pllBox->llBoxNm)+1, "boxToBeDelName");
	strcpy(str_name, pllBox->llBoxNm);

	/// TODO: free remaining ll node
	/// NOTE: pllBox->pMutex will be freed in the end, since still in used
	pllBox->pMutex=NULL;
	FREE(pllBox->llBoxNm, "str_name_init");
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


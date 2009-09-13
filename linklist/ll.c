/*#########################################################################
  ##  FILENAME: ll.c
  ##
  ##  DESC: first-in first-out link-list
  ##  USAGE:
  ##  IMP NOTE:
  ##  COMPILATION:
  ##  gcc -D_GNU_SOURCE -c mem memDebug.c memDebug.h
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
  ==  DESC: all node to pllBox
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE:
  =========================================================================*/
void add_ll(MODIF llBox * pllBox, MODIF ll *pll)
{
	pthread_mutex_lock(pllBox->pMutex);
	if(NULL==pllBox->pTail){
		/// link-list is empty
		assert(NULL==pllBox->pHead);
		pllBox->pHead=(ll *)MALLOC(sizeof(ll), pllBox->llBoxNm);
		pllBox->pTail=pllBox->pHead;
	}else{
		ll * pllnew = (ll *) MALLOC(sizeof(ll), pllBox->llBoxNm);
		pllBox->pTail->pNext=pllnew;
	}

	++pllBox->total;
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
	str_name = (char *) MALLOC(strlen(pllBox->llBoxNm), "boxToBeDelName");
	strcpy(str_name, pllBox->llBoxNm);
	printf("str_name=%s\n", str_name);

	/// TODO: free remaining ll node
	/// NOTE: pllBox->pMutex will be freed in the end, since still in used
	pllBox->pMutex=NULL;
	FREE(pllBox->llBoxNm, "str_name_init");
	pllBox->llBoxNm=NULL;
	FREE(pllBox, str_name);
	pllBox=NULL;

	FREE(str_name, "boxToBeDelName");
	str_name=NULL;
	pthread_mutex_unlock(pllBox->pMutex);

	/// freeing pllBox->pMutex
	pthread_mutex_destroy(pllBox->pMutex);
	FREE(pMutexTemp, "llMutex");
	pMutexTemp=NULL;
}

int main(void)
{
	llBox * myll=NULL;
	init_ll(&myll);
	if(NULL==myll){
		PERROR("Err! init_ll() failed to allocate\n");
	}
	crop_memPrintTable();
	end_ll(&myll);
	crop_memPrintTable();

}

//NOTE: mutex must be destroyed with pthread_mutex_destroy() before freeing or 
//reusing mutex storage.

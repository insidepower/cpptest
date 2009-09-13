/*==========================================================================
  ==  INCLUDES
  ==========================================================================*/
#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include "memDebug.h"
/*==========================================================================
  ==  MACRO DEFINE
  ==========================================================================*/
/*==========================================================================
  ==  MACRO CONSTANTS
  ==========================================================================*/
/// CONST: to indicate that a parameter/argument is constant input
#define CONST
/// MODIF: to indicate that a parameter/argument is modificable result
#define MODIF
/// MAX_FILE_NM_LEN: the maximum length of name used
#define MAX_FILE_NM_LEN			(10)
/// MAX_LL_INIT_CALL: the maximum number of times init can be callecd
#define MAX_LL_INIT_CALL 		(99999)
/*==========================================================================
  == STRUCT DEFINITION
  ==========================================================================*/
typedef struct ll_tag
{
	struct ll_tag * pNext;		//next in link-list
	void * pv;					//void pointer to content/struct
}ll;

typedef struct llBox_tag
{
	pthread_mutex_t * pMutex;	//mutex used by this llBox
	ll * pHead;					//head of link-list
	ll * pTail;					//tail of link-list
	int total;					//total node in this llBox
	char * llBoxNm;				//name of llBox
}llBox;
/*==========================================================================
  ==  MACRO FUNCTION
  ==========================================================================*/
#define PERROR(A)	printf("[%10s:%-4d] %s", __FILE__, __LINE__, A)
/*==========================================================================
  ==  ENUMERATIONS
  ==========================================================================*/
/*==========================================================================
  ==  GLOBAL VARIABLES
  ==========================================================================*/
/*==========================================================================
  ==  TYPEDEF
  ==========================================================================*/
/*==========================================================================
  == EXTERN GLOBAL VARIABLES
  ==========================================================================*/
/*==========================================================================
  ==  DSP/BIOS OBJECTS (DECLARED STATICALLY)
  ==========================================================================*/
/*==========================================================================
  ==  FUNCTION PROTOTYPES
  ==========================================================================*/

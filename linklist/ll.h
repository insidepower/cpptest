#ifndef __LL_H__
#define __LL_H__
/*==========================================================================
  ==  INCLUDES
  ==========================================================================*/
#include <semaphore.h>

/*==========================================================================
  ==  MACRO DEFINE
  ==========================================================================*/
#define SOK_ADD_LL			(0)
#define ERR_ADD_LL			(-1)
/*==========================================================================
  ==  MACRO CONSTANTS
  ==========================================================================*/
//CONST: to indicate that a parameter/argument is constant input
// CONST definition can be found in <dsplink.h:55>
//#define CONST
/// indicate that the parameter passed in maybe modified by the function
#define OUT
/// MAX_FILE_NM_LEN: the maximum length of name used
#define MAX_FILE_NM_LEN			(20)
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
	sem_t * pSem;				//semaphore for multiple writers and 1 reader
	int total;					//total node in this llBox
	const char * llBoxNm;			//name of llBox
	char * llBoxNodeNm;				//name of llBox
}llBox;
/*==========================================================================
  ==  MACRO FUNCTION
  ==========================================================================*/
#define PERROR(A)	printf("[%10s:%-4d] Err! %s", __FILE__, __LINE__, A)
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
void init_ll(llBox ** p_pllBox, const char * strllBoxNm);
int add_ll(OUT llBox * pllBox, OUT void **ppv);
void end_ll(OUT llBox ** p_pllBox);
void rm_ll(OUT llBox * pllBox, void **pv);
void get_ll(OUT llBox * pllBox, void **pv);
void get_ll_total(const llBox * pllBox, int * pTotal);
void print_ll(const llBox * pllBox, void (*pvPrint)(void * pv));
#endif //__LL_H__

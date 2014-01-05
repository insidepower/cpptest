#ifndef __MEMDEBUG_H__
#define __MEMDEBUG_H__

#include <stdlib.h>
#include <string.h>
#include <semaphore.h>

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

/* =========================== <typedef> =========================== */
typedef enum {
   B_NO=0, 
   B_YES
}BOOL; 

typedef enum {
   F_ERR=0,
   F_NO_ERR
}FLAG;

typedef struct mem_log_tag {
   struct mem_log_tag * pNext;
   unsigned char * ptr; //will include 2*FENCE_TOP+data+2*FENCE_BOTTOM
   unsigned char * ptr_start;
   unsigned char * ptr_end;
   int len;
   int used; //may be wrong for array/overlapping memcpy, used as ref only
   int freqUsage;
   char * objName; //try to use different variable name to help in debug
   const char * fileId;
   int isArray;
} memLogObj;

/* ==================== <function prototype> ======================= */
void crop_memPrintData(void * pChar, int size);
unsigned char * crop_malloc(int size, char * objName, int line, const char * fileId, int thread_id, int pid);
void crop_memPrintTable(void);
void crop_memPrintTableIndex(memLogObj * pMemObj);
void crop_memPrintTableNoArr(void);
FLAG crop_memChkData(unsigned char * pChar);
FLAG crop_memChkFence(int line, const char * fileId);
FLAG crop_memcpy(void * pDest, const void * pSrc, 
      int size, char * objName, int line, const char * fileId);
FLAG crop_memset(void * p_Dest, const unsigned char p_CharPattern, 
      int size, char * objName, int line, const char * fileId);
FLAG crop_free(void * p_ptr, char * objName, int line, const char * fileId);
FLAG crop_mark(unsigned char * pChar, int size, char * objName, int line, const char * fileId);
void crop_marray(void * pArr, int size, char * objName, int line, const char * fileId);
void crop_marray_shared(void * p_Arr, int size, char * objName, int line, const char * fileId);


/* ==================== <MACRO define> ======================= */
#define FENCE_BORDER 0xFACADE69
#define FENCE_TOP 4
#define FENCE_BOTTOM 4
#define FENCE_BYTE_TOTAL   2*(FENCE_TOP+FENCE_BOTTOM)
#define GARBAGE 0xCD
#define MEM_LOG_ARR_SIZE 3000

/* no mem log should be printed for this assertion error */
#define NO_LOG NULL
#define UNNAMED NULL

/* define File ID */
#define MAIN_C 1
#define MEMDEBUG_C 2

/* ON OFF SWITCH */
#define DEBUG_MEM

/* replace CROP_* with correct function */
#ifdef DEBUG_MEM 
#define CROP_MALLOC(A, B) crop_malloc(A, B, __LINE__, __FILE__, pthread_self(), getpid())
#define CROP_MEMCPY(A, B, C, D) crop_memcpy(A, B, C, D, __LINE__, __FILE__)
#define CROP_FREE(A, B) crop_free(A, B, __LINE__, __FILE__)
#define CROP_MARK(A, B, C) crop_mark(A, B, C, __LINE__, __FILE__)
#define CROP_MARRAY(A, B, C) crop_marray(A, B, C, __LINE__, __FILE__)
#define CROP_MARRAY_SHARED(A, B, C) crop_marray_shared(A, B, C, __LINE__, __FILE__)
#define CROP_MEMSET(A, B, C, D) crop_memset(A, B, C, D, __LINE__, __FILE__)
#define CROP_FREE_ARR(A, B) crop_free(A, B, __LINE__, __FILE__)

/*
#define CROP_MALLOC(A, B, C) crop_malloc(A, B, __LINE__, __FILE__)
#define CROP_MEMCPY(A, B, C, D, E) crop_memcpy(A, B, C, D, __LINE__, __FILE__)
#define CROP_FREE(A, B, C) crop_free(A, B, __LINE__, __FILE__)
#define CROP_MARK(A, B, C, D) crop_mark(A, B, C, __LINE__, __FILE__)
#define CROP_MARRAY(A, B, C, D) crop_marray(A, B, C, __LINE__, __FILE__)
#define CROP_MEMSET(A, B, C, D, E) crop_memset(A, B, C, D, __LINE__, __FILE__)
#define CROP_FREE_ARR(A, B, C) crop_free(A, B, __LINE__, __FILE__)
*/
#else
#define CROP_MALLOC(A, B) (unsigned char *) malloc(A); assert(A!=0)
#define CROP_MEMCPY(A, B, C, D) memcpy(A, B, C)
#define CROP_FREE(A, B) free(A)
#define CROP_MARK(A, B, C) NULL
#define CROP_MARRAY(A, B, C) NULL
#define CROP_MEMSET(A, B, C, D) 
#define CROP_FREE_ARR(A, B) NULL 
#endif
/* ==================== <global variable> ======================= */

extern memLogObj * pMemHead;
extern memLogObj * pMemTail;
extern unsigned char fenceByte[4];
extern pthread_mutex_t mutex_node;
#endif

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


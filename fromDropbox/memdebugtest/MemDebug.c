#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include "MemDebug.h"

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

#define FID MEMDEBUG_C

void throwErr(int line, const char * fileId, memLogObj * pMemObj);
void crop_memPrintRange(void * p_Dest);

int gTotalMemNode=0;
memLogObj * pMemHead = NULL;
memLogObj * pMemTail = NULL;
int gDebugLine=0;
char * gDebugSrc;
char gDebugMsg[2][80];
memLogObj * gDebugMemObj;
unsigned char * gDebugMsgValue[2];
//pthread_mutex_t mutexRecursive=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexRecursive=PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
//pthread_mutex_t mutex_removeNode=PTHREAD_MUTEX_INITIALIZER;
unsigned char fenceByte[4]={0xFA, 0xCA, 0xDE, 0x69};

#ifdef DEBUG_MEM
#define CROP_ASSERT(A, B, C, D) \
   if(A)\
      NULL;\
   else\
      throwErr(B,C, D);\
      assert(A)
#else
#define CROP_ASSERT(A, B, C, D) assert(A)
#endif

void throwErr(int line, const char * fileId, memLogObj * pMemObj)
{
   printf("\n\nAssertion failed @ %s:%d\n", fileId, line);
   printf("Origin from %s:%d, gDebugMsg(%s), gDebugMsgValue(%p)\n", gDebugSrc, gDebugLine, gDebugMsg, gDebugMsgValue[0]);
   /*
   if(gDebugMsgValue[0]!=NULL && crop_memChkData(gDebugMsgValue[0], &gDebugMemObj))
   {
      crop_memPrintTableIndex(gDebugMemObj);
      crop_memPrintData(pMemObj->ptr, 16);
      crop_memPrintData(pMemObj->ptr_end-8, 16);
   }
   */
   if(pMemObj != NO_LOG)
   {
      crop_memPrintTableIndex(pMemObj);
      if(pMemObj->isArray==0)
      {
	 printf("throwErr: (8)FENCE_TOP+(8)Data: \n");
	 crop_memPrintData(pMemObj->ptr, 16);
	 printf("throwErr: (8)Data+(8)FENCE_BOTTOM: \n");
	 crop_memPrintData(pMemObj->ptr_end-8, 16);
      }
   }
}

int addNode(memLogObj * newNode, int line, const char * fileId, int thread_id, int pid)
{
   //if(pthread_mutex_lock(&mutexRecursive)!=0)
   //{
      //printf("addNode: Error in pthread_mutex_lock\n");
      //fflush(stdout);
   //}
   //printf("addNode - start (%s:%d, thread(%d), pid(%d)\n", fileId, line, thread_id, pid);
   if(0 == gTotalMemNode)
   {
      pMemHead=newNode;
      pMemTail=pMemHead;
   }
   else
   {
      pMemTail->pNext=newNode;
      pMemTail = newNode;
   }
   gTotalMemNode++;
   //printf("addNode - end (%s:%d, thread(%d), pid(%d) data(%p)\n", fileId, line, thread_id, pid, newNode->ptr_start);
   //if(pthread_mutex_unlock(&mutexRecursive) != 0)
   //{
      //printf("addNode: Error in pthread_mutex_lock\n");
      //fflush(stdout);
   //}
   return 0;
}

/* ******************************************************************
 * parameter p_Prev passed is the object b4 the object 
 * to be deleted 
 * *****************************************************************/
int removeNode(memLogObj * p_Prev, memLogObj * p_ToBeDeleted, int line, const char * fileId)
{
   //pthread_mutex_lock(&mutexRecursive);
   //printf("removeNode - start (%s:%d)\n", fileId, line);
   assert(gTotalMemNode>0);
   //crop_memPrintTable();
   if (gTotalMemNode == 1) //last node
   {
      CROP_ASSERT(p_ToBeDeleted==p_Prev && p_ToBeDeleted==pMemHead && p_ToBeDeleted==pMemTail, __LINE__, __FILE__, p_ToBeDeleted);
      if(p_Prev->isArray==0)
      {
	 memset(p_Prev->ptr, GARBAGE, p_Prev->len+FENCE_BYTE_TOTAL);
	 free(p_Prev->ptr);
      }
      else //isArray
      {
	 memset(p_Prev->ptr, GARBAGE, p_Prev->len);
      }
      free(p_Prev);
      pMemHead = NULL;
      pMemTail = NULL;
   }
   else
   {
      //do proper link up by removing memLogObj to be deleted
      if(p_Prev != p_ToBeDeleted) //to be deleted is not pMemHead
      {
	 if(pMemTail == p_ToBeDeleted)
	 {
	    pMemTail = p_Prev; 
	 }
	 p_Prev->pNext = p_ToBeDeleted->pNext;
      }
      else if(p_ToBeDeleted == pMemHead)
      {
	 CROP_ASSERT(p_ToBeDeleted==p_Prev, __LINE__, __FILE__, p_ToBeDeleted);
	 pMemHead = pMemHead->pNext;
      }

      //proceed to delete... 
      if(p_ToBeDeleted->isArray==0)
      {
	 memset(p_ToBeDeleted->ptr, GARBAGE, p_ToBeDeleted->len+FENCE_BYTE_TOTAL);
	 free(p_ToBeDeleted->ptr);
      }
      else //isArray
      {
	 memset(p_ToBeDeleted->ptr, GARBAGE, p_ToBeDeleted->len);
      }
      free(p_ToBeDeleted);
   }
   gTotalMemNode--;
   //printf("removeNode - end (%s:%d - free (%p)\n", fileId, line, p_ToBeDeleted->ptr_start);
   //pthread_mutex_unlock(&mutexRecursive);
   return 0;
}


unsigned char * crop_malloc(int size, char * objName, int line, const char * fileId, int thread_id, int pid)
{
   unsigned char * ptr;
   unsigned char * pFence;
   memLogObj * pMemObj = NULL;
   //printf("crop_malloc: size (%d), objName(%s), fileId(%s)\n",
	 //size, objName, fileId);
  
   CROP_ASSERT(size > 0,line, fileId, NO_LOG);
   CROP_ASSERT(((objName != NULL) && (fileId != NULL)),line, fileId, NO_LOG);

   pthread_mutex_lock(&mutexRecursive);
   ptr = malloc(size+FENCE_BYTE_TOTAL);
   CROP_ASSERT(ptr!=NULL,line, fileId, NO_LOG);

   //fence-top
   pFence = ptr;
   memcpy(pFence, fenceByte, FENCE_TOP);
   memcpy(pFence+FENCE_TOP, fenceByte, FENCE_TOP);

   //fence-bottom
   pFence = ptr+2*FENCE_TOP+size;
   memcpy(pFence, fenceByte, FENCE_BOTTOM);
   memcpy(pFence+FENCE_BOTTOM, fenceByte, FENCE_BOTTOM);

   //initialize to known value
   memset(ptr+2*FENCE_TOP, GARBAGE, size);

   pMemObj = (memLogObj *) malloc(sizeof(memLogObj));
   assert(sizeof(memLogObj)==40);
   CROP_ASSERT(pMemObj, line, fileId, NO_LOG);
   pMemObj->pNext = NULL;
   pMemObj->ptr=ptr; //ptr start with 2*FENCE_TOP before actual data
   pMemObj->ptr_start=ptr+2*FENCE_TOP;
   pMemObj->ptr_end=pMemObj->ptr_start+size;
   pMemObj->len=size;
   pMemObj->used=0;
   pMemObj->freqUsage=0;
   pMemObj->objName=objName;
   pMemObj->fileId=fileId;
   pMemObj->isArray=0; //if ptr is not Array, then isArray=0
   addNode(pMemObj, line, fileId, thread_id, pid);

   crop_memChkFence(line, fileId);
   if(gTotalMemNode >= MEM_LOG_ARR_SIZE)
   {
      printf("gTotalMemNode(%d) exceed table size (%d)\n", gTotalMemNode, MEM_LOG_ARR_SIZE);
      fflush(stdout);
      abort();
   }

   //crop_memPrintData(ptr, size+FENCE_BYTE_TOTAL);
   pthread_mutex_unlock(&mutexRecursive);
   return (pMemObj->ptr_start);
}

FLAG crop_memcpy(void * p_Dest, const void * p_Src, 
      int size, char * objName, int line, const char * fileId)
{
   int i=0;
   memLogObj * pTemp;
   unsigned char * pDest = (unsigned char *) p_Dest;
   unsigned char * pSrc = (unsigned char *) p_Src;

   CROP_ASSERT(pMemHead != NULL, line, fileId, NO_LOG);
   CROP_ASSERT((pDest != NULL && pSrc != NULL && size > 0),line, fileId, NO_LOG);

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   for(;i<gTotalMemNode;)
   {
      //printf("range: up(%p) <= pDest < down(%p); len(%d)\n", pTemp->ptr+fenceByte, pTemp->ptr+fenceByte+pTemp->len, pTemp->len);
      if(pDest >= (pTemp->ptr_start) && pDest < (pTemp->ptr_end)) 
      {
	 //printf("memcpy: pDest(%p) found\n");
	 if(objName != UNNAMED)
	 {
	    CROP_ASSERT(strcmp(objName, pTemp->objName)==0,line, fileId, pTemp);
	 }
	 if((pDest+size) > pTemp->ptr_end) //write exceeding boundary
	 {
	    printf("\n\ncrop_memcpy: Error! (pDest+size) > (pTemp->ptr_end)\n");
	    printf("crop_memcpy: Error! pTemp->ptr_start(%p), pTemp->len(%d)\n", pTemp->ptr_start, pTemp->len);
	    printf("crop_memcpy: pDest=%p, pSrc=%p, size=%d, objName=%s, line=%d, fileId=%s\n",
		     pDest, pSrc, size, objName, line, fileId);
	    crop_memPrintTableIndex(pTemp);
	    CROP_ASSERT(NULL,line, fileId, NO_LOG);
	    break;
	 }
	 memcpy(pDest, pSrc, size);
	 crop_memChkFence(line, fileId);
	 //--TODO: Array size might not be correct, since array is local
	 //variable variable, it is re-initialize every time
	 //--TODO: pointer size might not be correct, if memcpy is overlapping
	 pTemp->used+=size;
	 ++pTemp->freqUsage;
	 //crop_memPrintTable();
	 //crop_memPrintData(pTemp->ptr, pTemp->len);

	 pthread_mutex_unlock(&mutexRecursive);
	 return F_NO_ERR;
      }
      ++i;
      pTemp = pTemp->pNext;
   }
   printf("\n\ncrop_memcpy: Error! Variable is not allocated in memory\n");
   printf("crop_memcpy: pDest=%p, pSrc=%p, size=%d, objName=%s, line=%d, fileId=%s\n",
	 pDest, pSrc, size, objName, line, fileId);
   //crop_memPrintRange(pDest);
   crop_memPrintTable();
   CROP_ASSERT(NULL,line, fileId, NO_LOG);

   pthread_mutex_unlock(&mutexRecursive);
   return F_ERR;
}


FLAG crop_memset(void * p_Dest, unsigned char p_CharPattern, 
      int size, char * objName, int line, const char * fileId)
{

   int i=0;
   memLogObj * pTemp;
   unsigned char * pDest = (unsigned char *) p_Dest;

   CROP_ASSERT(pMemHead != NULL, line, fileId, NO_LOG);
   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   CROP_ASSERT((pDest != NULL && size > 0),line, fileId, NO_LOG);
   for(;i<gTotalMemNode;)
   {
      if(pDest >= (pTemp->ptr_start) && pDest < (pTemp->ptr_end)) 
      {
	 if(objName != UNNAMED)
	 {
	    CROP_ASSERT(strcmp(objName, pTemp->objName)==0,line, fileId, pTemp);
	 }
	 if(((pDest+size) > (pTemp->ptr_end))) //write exceeding boundary
	 {
	    printf("crop_memset: Error! (pDest+size) > (pTemp->ptr_end)\n");
	    printf("crop_memset: Error! pTemp->ptr(%p), pTemp->len(%d)\n", pTemp->ptr, pTemp->len);
	    break;
	 }
	 memset(pDest, p_CharPattern, size);
	 //crop_memPrintData(pTemp->ptr, pTemp->len);
	 crop_memChkFence(line, fileId);
	 pTemp->used+=size;
	 ++pTemp->freqUsage;
	 //crop_memPrintTable();

	 pthread_mutex_unlock(&mutexRecursive);
	 return F_NO_ERR;
      }
      ++i;
      pTemp = pTemp->pNext;
   }
   printf("crop_memset: Error! Variable is not allocated in memory\n");
   printf("crop_memset: pDest=%p, p_CharPattern=%c, size=%d, objName=%s, fileId=%s\n",
	 pDest, p_CharPattern, size, objName, fileId);
   crop_memPrintTable();
   CROP_ASSERT(NULL,line, fileId, NO_LOG);

   pthread_mutex_unlock(&mutexRecursive);
   return F_ERR;
}

FLAG crop_free(void * p_ptr, char * objName, int line, const char * fileId)
{
   int i=0;
   memLogObj * pTemp;
   memLogObj * pPrev;
   unsigned char * pChar = (unsigned char *) p_ptr;

   CROP_ASSERT(pMemHead != NULL, line, fileId, NO_LOG);
   CROP_ASSERT((pChar != NULL && fileId != NULL),line, fileId, NO_LOG);
   //CROP_ASSERT(objName != NULL, line, fileId, NO_LOG);

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   pPrev = pMemHead;
   for(;i<gTotalMemNode;)
   {
      //printf("range %d: up(%p) <= pDest < down(%p); len(%d)\n", i, pTemp->ptr+fenceByte, pTemp->ptr+fenceByte+pTemp->len, pTemp->len);
      if(pChar >= (pTemp->ptr_start) && pChar < (pTemp->ptr_end)) 
      {
	 if(objName != UNNAMED)
	 {
	    CROP_ASSERT((strcmp(objName, pTemp->objName)==0),line, fileId, pTemp);
	 }
	 crop_memChkFence(line, fileId);
	 removeNode(pPrev, pTemp, line, fileId);

	 pthread_mutex_unlock(&mutexRecursive);
	 return F_NO_ERR;
      }
      ++i;
      pPrev = pTemp;
      pTemp = pTemp->pNext;
   }
   printf("\n\nError! trying to free a non-existing memory: pData(%p), objName(%s)\n", pChar, objName);
   crop_memPrintTable();
   CROP_ASSERT(NULL, line, fileId, NO_LOG);

   pthread_mutex_unlock(&mutexRecursive);
   return F_ERR;
}

/* *******************************************************************
 * crop_mark should be called before any data is written to a memory
 * so that the memory would be marked as used. crop_mark should not be
 * called if crop_memcpy has been called.
 * e.g.
 * unsigned char * mydata = CROP_MALLOC(...);
 * CROP_MARK(...);
 * mydata[0]=0xAA;
 * *******************************************************************/
FLAG crop_mark(unsigned char * pChar, int size, char * objName, int line, const char * fileId)
{
   int i=0;
   memLogObj * pTemp;

   CROP_ASSERT(pMemHead != NULL, line, fileId, NO_LOG);
   CROP_ASSERT(pChar!=NULL && size > 0 && fileId != NULL,line, fileId, NO_LOG);

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   for(;i<gTotalMemNode;)
   {
      if(pChar >= (pTemp->ptr_start) && pChar < (pTemp->ptr_end)) 
      {
	 if(objName != UNNAMED)
	 {
	    CROP_ASSERT(strcmp(objName, pTemp->objName)==0,line, fileId, pTemp);
	 }
	 if(((pChar+size) > pTemp->ptr_end)) //write exceeding boundary
	 {
	    printf("crop_mark: Error! (pDest+size) > (pTemp->ptr_end)\n");
	    printf("crop_mark: Error! pTemp->ptr(%p), pTemp->len(%d)\n", pTemp->ptr, pTemp->len);
	    printf("crop_mark: pChar=%p, size=%d, objName=%s, fileId=%s\n",
			pChar, size, objName, fileId);
	    crop_memPrintTableIndex(pTemp);
	    CROP_ASSERT(NULL,line, fileId, NO_LOG);
	    break;
	 }
	 CROP_ASSERT(size <= pTemp->len,line, fileId, pTemp);
	 crop_memChkFence(line, fileId);
	 pTemp->used+=size;
	 ++pTemp->freqUsage;
	 //crop_memPrintTable();

	 pthread_mutex_unlock(&mutexRecursive);
	 return F_NO_ERR;
      }
      ++i;
      pTemp=pTemp->pNext;
   }
   printf("\n\ncrop_mark: variable not found!\n");
   printf("crop_mark: pChar=%p, size=%d, objName=%s, fileId, i=%s\n",
	 pChar, size, objName, fileId);
   crop_memPrintTable();
   CROP_ASSERT(NULL,line, fileId, NO_LOG);

   pthread_mutex_unlock(&mutexRecursive);
   return F_ERR;
}

/* add an entry in the memory log for array type of variable */
void crop_marray(void * p_Arr, int size, char * objName, int line, const char * fileId)
{
   memLogObj * pMemObj = NULL;

   int i=0;
   memLogObj * pTemp;
   unsigned char * pArr = (unsigned char *) p_Arr;

   CROP_ASSERT(pArr!=NULL && size > 0 && objName != NULL && fileId != NULL,line, fileId, NO_LOG);

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   for(;i<gTotalMemNode;)
   {
      //printf("range: up(%p) <= pDest < down(%p); len(%d)\n", pTemp->ptr+fenceByte, pTemp->ptr+fenceByte+pTemp->len, pTemp->len);
      if(pArr >= (pTemp->ptr_start) && pArr < (pTemp->ptr_end)) 
      {
	 crop_memChkFence(line, fileId);
	 //crop_memPrintData(pTemp->ptr, pTemp->len);
	 printf("\n\ncrop_marray: Error! variable exist! pArr(%p), objName(%s), size(%d)\n", pArr, objName, size);
	 CROP_ASSERT(NULL, line, fileId, pTemp);
      }
      ++i;
      pTemp = pTemp->pNext;
   }
   pMemObj = (memLogObj *) malloc(sizeof(memLogObj));
   CROP_ASSERT(pMemObj, line, fileId, NO_LOG);
   pMemObj->pNext = NULL;
   pMemObj->ptr=pArr;
   pMemObj->ptr_start=pArr;
   pMemObj->ptr_end=pMemObj->ptr_start+size;
   pMemObj->len=size;
   pMemObj->used=0;
   pMemObj->freqUsage=0;
   pMemObj->objName=objName;
   pMemObj->fileId=fileId;
   pMemObj->isArray=1;
   addNode(pMemObj, line, fileId, 0, 0);

   //memset(pMemObj->ptr, GARBAGE, size);

   pthread_mutex_unlock(&mutexRecursive);
   //crop_memPrintTableIndex(pMemObj);
}

/* this function is for the use of dsp-gpp shared memory
 * since gpp would not know in advance which memory will be allocated by dsp
 * gpp would not be able to log all memory usage in advanced
 * therefore whenever gpp receive the memory exchanged from dsp
 * it would try to log the memory using crop_marray_shared */
void crop_marray_shared(void * p_Arr, int size, char * objName, int line, const char * fileId)
{
   static unsigned char * arrBuf[8];
   static int arrBuf_count = 0;
   unsigned char * pArr = (unsigned char *) p_Arr;
   int i;

   for(i=0; i<arrBuf_count; i++)
   {
      if(pArr == arrBuf[i])
      {
	 //found, return
	 return;	  
      }
   }
   //if not found, add to log
   arrBuf[arrBuf_count++]=pArr;
   crop_marray(p_Arr, size, objName, line, fileId);
}

/*
FLAG crop_freeArray(void * p_Arr, const char * objName, int line, const char * fileId)
*/

/* IMPORTANT: caller of crop_memChkFence should be protected with 
   pthread_mutex_lock(&mutexRecursive); or error might occur! As gTotalMemNode could 
   be modified by other function..
   */
FLAG crop_memChkFence(int line, const char * fileId)
{
   int i=0;
   memLogObj * pTemp;

   gDebugLine=line;
   gDebugSrc=(char *) fileId;
   
   pthread_mutex_lock(&mutexRecursive);
   pTemp=pMemHead;
   for(;i<gTotalMemNode;i++)
   {
      if(pTemp->isArray==0)
      {
	 //strcpy(&gDebugMsg[0][0], "pTemp->ptr_start");
	 //gDebugMsgValue[0]=pTemp->ptr_start;
	 CROP_ASSERT(0==strncmp((const char *) fenceByte, (const char *) pTemp->ptr, FENCE_TOP), __LINE__, __FILE__, pTemp);
	 CROP_ASSERT(0==strncmp((const char *) fenceByte, (const char *) pTemp->ptr+FENCE_TOP, FENCE_TOP),__LINE__, __FILE__, pTemp);
	 CROP_ASSERT(0==strncmp((const char *) fenceByte, (const char *) pTemp->ptr_end, FENCE_BOTTOM),__LINE__, __FILE__, pTemp);
	 CROP_ASSERT(0==strncmp((const char *) fenceByte, (const char *) pTemp->ptr_end+FENCE_BOTTOM, FENCE_BOTTOM),__LINE__, __FILE__, pTemp);
      }
      pTemp = pTemp->pNext;
   }
   //gDebugMsg[0][0]='\0';
   //gDebugMsgValue[0]=0;
   gDebugLine=0;
   gDebugSrc=NULL;

   pthread_mutex_unlock(&mutexRecursive);
   return F_NO_ERR;
}

void crop_memPrintTable(void)
{
   int i=0;
   memLogObj * pTemp;

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   printf("===========================================================================\n");
   printf("%-4sptr\t\tlen\tused\tfreq\tisArray\tobjName      \tfileId\n", "no.");
   printf("===========================================================================\n");
   for(;i < gTotalMemNode;i++)
   {
      printf("%-4d%-10p\t%d\t%d\t%d\t%d\t%-15s\t%s\n", i,
	    pTemp->ptr, 
	    pTemp->len,
	    pTemp->used,
	    pTemp->freqUsage,
	    pTemp->isArray,
	    pTemp->objName,
	    pTemp->fileId);
      pTemp = pTemp->pNext;
   }
   fflush(stdout);

   pthread_mutex_unlock(&mutexRecursive);
}

void crop_memPrintTableNoArr(void)
{
   int i=0;
   memLogObj * pTemp;
   

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   printf("===========================================================================\n");
   printf("%-4sptr\t\tlen\tused\tfreq\tisArray\tobjName      \tfileId\n", "no.");
   printf("===========================================================================\n");
   for(;i < gTotalMemNode;i++)
   {
      if(pTemp->isArray==0)
      {
	 printf("%-4d%-10p\t%d\t%d\t%d\t%d\t%-15s\t%s\n", i,
	       pTemp->ptr, 
	       pTemp->len,
	       pTemp->used,
	       pTemp->freqUsage,
	       pTemp->isArray,
	       pTemp->objName,
	       pTemp->fileId);
      }
      pTemp = pTemp->pNext;
   }
   fflush(stdout);

   pthread_mutex_unlock(&mutexRecursive);
}
void crop_memPrintTableIndex(memLogObj * pMemObj)
{
   //int i=index;

   pthread_mutex_lock(&mutexRecursive);
   printf("===========================================================================\n");
   printf("ptr\t\tlen\tused\tfreq\tisArray\tobjName     \tfileId\n");
   printf("===========================================================================\n");
   printf("%-10p\t%d\t%d\t%d\t%d\t%-15s\t%s\n", 
	 pMemObj->ptr, 
	 pMemObj->len,
	 pMemObj->used,
	 pMemObj->freqUsage,
	 pMemObj->isArray,
	 pMemObj->objName,
	 pMemObj->fileId);
   fflush(stdout);
   pthread_mutex_unlock(&mutexRecursive);
}

void crop_memPrintRange(void * p_Dest)
{
   int i=0;
   memLogObj * pTemp;
   unsigned char * pDest = (unsigned char *) p_Dest;

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   for(;i<gTotalMemNode;)
   {
      printf("range: up(%p) <= pDest < down(%p); len(%d)\n", pTemp->ptr_start, pTemp->ptr_end, pTemp->len);
      if(pDest >= (pTemp->ptr_start) && pDest < (pTemp->ptr_end)) 
      {
	 printf("pDest (%p) found!\n", pDest);
	 fflush(stdout);
	 pthread_mutex_unlock(&mutexRecursive);
	 return;
      }
      ++i;
      pTemp = pTemp->pNext;
   }
   printf("pDest (%p) not in range\n");
   pthread_mutex_unlock(&mutexRecursive);
}

FLAG crop_memChkData(unsigned char * pChar)
{
   int i=0;
   memLogObj * pTemp;

   pthread_mutex_lock(&mutexRecursive);
   pTemp = pMemHead;
   CROP_ASSERT(pChar!= NULL, __LINE__, __FILE__, NO_LOG);
   for(;i<gTotalMemNode;)
   {
      if(pChar >= (pTemp->ptr_start) && pChar < (pTemp->ptr_end)) 
      {
	 crop_memPrintTableIndex(pTemp);
	 pthread_mutex_unlock(&mutexRecursive);
	 return F_NO_ERR;
      }
      ++i;
      pTemp = pTemp->pNext;
   }
   printf("crop_memChkData: could not find %p\n", pChar);
   pthread_mutex_unlock(&mutexRecursive);
   return F_ERR;
}

/* *************************************************
 * print the content of allocated memory
 * ptr start before 2*FENCE_TOP 
 * ************************************************/
void crop_memPrintData(void * pChar, int size)
{
   unsigned char * ptr = (unsigned char *) pChar;
   int i=0;

   pthread_mutex_lock(&mutexRecursive);
   for(;i<size;i++)
   {
      printf("%2X, ", *ptr++);
      if(i>0 && (i+1)%10 == 0)
      {
	 printf("\n");
      }
   }
   printf("\n");
   fflush(stdout);
   pthread_mutex_unlock(&mutexRecursive);
}

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */


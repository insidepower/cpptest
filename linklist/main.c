/*#########################################################################
  ##  FILENAME: main.c
  ##
  ##  DESC: applicatin to try link list
  ##  USAGE:
  ##  IMP NOTE:
  ##  COMPILATION:
  ##  gcc -D_GNU_SOURCE -c -g -o mem memDebug.c
  ##  gcc -g ll.h mem ll.c main.c
  #########################################################################*/
/*==========================================================================
  ==  INCLUDES
  ==========================================================================*/
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include "ll.h"
#include "memDebug.h"
/*==========================================================================
  == STRUCT DEFINITION
  ==========================================================================*/
typedef struct userData
{
	char name[10];
	int seq;
}tdUserData;
/*++++++++++++++++++++++++++++< FUNCTION >++++++++++++++++++++++++++++++++*/

void print_userData(void * pv)
{
	tdUserData * ptd = (tdUserData *) pv;
	printf("name=%s, seq=%d\n", ptd->name, ptd->seq);
}

int main(void)
{
	//--------------------------------------------  init //
	llBox * myll=NULL;
	init_ll(&myll, "llBoxCap0");
	if(NULL==myll){
		PERROR("init_ll() failed to allocate\n");
		crop_memPrintTable();
		return -1;
	}

	//------------------------------------------------- add node //
	int cnt=1;
	//ll * pll=NULL;
	tdUserData * ptdUserData = NULL;
	ptdUserData = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData");
	strcpy(ptdUserData->name, "haha1");
	ptdUserData->seq=cnt++;
	add_ll(myll, (void **)&ptdUserData);
	//assert(NULL!=pll);
	//pll->pv=ptdUserData;

	//assert(NULL!=pll);
	ptdUserData = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData");
	//pll->pv=ptdUserData;
	strcpy(ptdUserData->name, "haha2");
	ptdUserData->seq=cnt++;
	add_ll(myll, (void **)&ptdUserData);

	//------------------------------------------------- traverse node //
	print_ll(myll, &print_userData);
	crop_memPrintTable();

	//------------------------------------------------- delete node //
	printf("deleting 1\n");
	rm_ll(myll, (void **) &ptdUserData);
	FREE(ptdUserData, "tdUserData");
	crop_memPrintTable();
	printf("deleting 2\n");
	rm_ll(myll, (void **) &ptdUserData);
	FREE(ptdUserData, "tdUserData");
	crop_memPrintTable();

	//------------------------------------------- add node (test semaphore)//
	//ll * pll2=NULL;
	tdUserData * ptdUserData2 = NULL;
	ptdUserData2 = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData2");
	//assert(NULL!=pll2);
	//pll2->pv=ptdUserData2;
	strcpy(ptdUserData2->name, "haha1");
	ptdUserData2->seq=cnt++;
	add_ll(myll, (void **)&ptdUserData2);

	//assert(NULL!=pll2);
	ptdUserData2 = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData2");
	//pll2->pv=ptdUserData2;
	strcpy(ptdUserData2->name, "haha2");
	ptdUserData2->seq=cnt++;
	add_ll(myll, (void **)&ptdUserData2);
	crop_memPrintTable();

	//------------------------------------------- get node (test semaphore)//
	printf("deleting 1\n");
	get_ll(myll, (void **) &ptdUserData2);
	FREE(ptdUserData2, "tdUserData2");
	crop_memPrintTable();
	printf("deleting 2\n");
	get_ll(myll, (void **) &ptdUserData2);
	FREE(ptdUserData2, "tdUserData2");
	crop_memPrintTable();

	//-------------------------------------------- end //
	crop_memPrintTable();
	end_ll(&myll);
	printf("Ending...\n");
	crop_memPrintTable();
	
	return 0;
}

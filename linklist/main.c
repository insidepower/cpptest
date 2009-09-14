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
	init_ll(&myll);
	if(NULL==myll){
		PERROR("Err! init_ll() failed to allocate\n");
	}

	//------------------------------------------------- add node //
	int cnt=1;
	ll * pll=NULL;
	tdUserData * ptdUserData = NULL;
	ptdUserData = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData");
	add_ll(&myll, &pll);
	assert(NULL!=pll);
	pll->pv=ptdUserData;
	strcpy(ptdUserData->name, "haha1");
	ptdUserData->seq=cnt++;

	add_ll(&myll, &pll);
	assert(NULL!=pll);
	ptdUserData = (tdUserData *) MALLOC(sizeof(tdUserData), "tdUserData");
	pll->pv=ptdUserData;
	strcpy(ptdUserData->name, "haha2");
	ptdUserData->seq=cnt++;

	//------------------------------------------------- traverse node //
	print_ll(myll, &print_userData);

	//------------------------------------------------- delete node //
	printf("deleting 1\n");
	rm_ll(&myll, (void **) &ptdUserData);
	FREE(ptdUserData, "tdUserData");
	crop_memPrintTable();
	printf("deleting 2\n");
	rm_ll(&myll, (void **) &ptdUserData);
	FREE(ptdUserData, "tdUserData");
	crop_memPrintTable();

	//-------------------------------------------- end //
	crop_memPrintTable();
	end_ll(&myll);
	printf("Ending...\n");
	crop_memPrintTable();
	
	return 0;
}

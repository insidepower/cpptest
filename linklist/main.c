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
	int total;
}tdUserData;
/*++++++++++++++++++++++++++++< FUNCTION >++++++++++++++++++++++++++++++++*/
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
	add_ll(myll, &pll);
	assert(NULL!=pll);
	pll->name[0]='1';
	pll->total=cnt++;

	add_ll(myll, &pll);
	assert(NULL!=pll);
	pll->name[0]='2';
	pll->total=cnt++;

	//-------------------------------------------- end //
	crop_memPrintTable();
	end_ll(&myll);
	crop_memPrintTable();

}

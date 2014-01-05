/*==============================================================================
  ==  INCLUDES
  ==============================================================================*/
#include <stdio.h>
#include <pthread.h>
#include <main.h>

/*++++++++++++++++++++++++++++++++< FUNCTION >+++++++++++++++++++++++++++++++++++*/
/*==============================================================================
 ==  @ main @
 ==
 ==  DESC:
 ==  USAGE:
 ==  INPUTS:
 ==  OUTPUTS:
 ==  RETURN:
 ==  IMP NOTE:
==============================================================================*/
int main(void)
{
	if(ERR_INIT_FAIL==initGppMac())
	{
	}

	do {
		gui_reset=0;
	
	}while(gui_reset);
	printf("Application terminated\n");
	return 0;
}

int initGppMac(void)
{
	return 0;
}

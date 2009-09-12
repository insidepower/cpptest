/*==============================================================================
 ==  @ main.c @
 ==
 ==  DESC: test the scope of statically declared variable
 ==  COMPILE: gcc main.c staticGlobalVar.c staticGlobalVar.h
 ==  RESULT: compilation failed with :
 ==          undefined reference to `staticGlobalVar`
==============================================================================*/
#include <stdio.h>
#include "staticGlobalVar.h"
extern int staticGlobalVar;

int main()
{
   printf("staticGlobalVar=%d\n",staticGlobalVar);
   return 0;
}

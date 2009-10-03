#include <stdio.h>
/*==========================================================================
  ==  MACRO DEFINE
  ==========================================================================*/
#define ENABLE_DEBUG_LL
/*==========================================================================
  ==  MACRO FUNCTION
  ==========================================================================*/
#ifdef ENABLE_DEBUG_LL
#define STR_LEN_CHECK(A,B) \
{\
	int strLenChk=A-B;\
	assert(strLenChk>0);\
}
#else
#define STR_LEN_CHECK NULL
#endif

#define PRINT printf

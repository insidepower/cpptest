#ifndef __MY_ASSERT_H__
#define __MY_ASSERT_H__

#include <stdlib.h>

/* define customized ASSERTION for ARM and DSP
 * The ASSERTION will check for statement condition 
 * unless NDEBUG is defined */
#ifdef NDEBUG
#define ASSERT(A) NULL

#else //NDEBUG
#ifdef TI_DSP
#define ASSERT(A) \
      if(!(A)){ \
	 SYS_error("Assertion failed at line: %s, fileName: %s\n", __LINE__, __FILE__);\
      }
#else //TI_DSP
#define ASSERT(A) \
      if(!(A)){ \
	 printf("Assertion failed at line: %s, fileName: %s\n", __LINE__, __FILE__);\
	 exit(EXIT_FAILURE);\
      }
#endif //TI_DSP
#endif //NDEBUG

#endif //__MY_ASSERT_H__

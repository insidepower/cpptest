/* Link List
 * Based on first in first out 
 */
#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#ifdef TI_DSP
/*  ----------------------------------- DSP/BIOS Headers            */
#include <std.h>
#include <log.h>
#include <swi.h>
#include <sys.h>
#include <sio.h>
#include <tsk.h>
#include <sem.h>

/*  ----------------------------------- DSP/BIOS LINK Headers       */
#include <failure.h>
#include <dsplink.h>
#include <platform.h>
#endif //TI_DSP

#include <stdio.h>
#include <assert.h>
#include <stdlib.h> //free()
#define GARBAGE 0xCD

typedef struct ll_tag
{
   struct ll_tag * pNext;
   unsigned char * pchData;
   int len;
} ll;



/* function prototype */
int addNode(ll * newNode);
int removeNode(void);
int traverselist(void);
int getTotalNode(void);

#endif 

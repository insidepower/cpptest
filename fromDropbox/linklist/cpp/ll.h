
/*********************************************************************
	Rhapsody	: 7.1 
	Login		: MatlabUser
	Component	: MAC 
	Configuration 	: MAC
	Model Element	: ll
//!	Generated Date	: Thu, 6, Aug 2009  
	File Path	: MAC/MAC/ll.h
*********************************************************************/
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifndef ll_H 

#define ll_H 

//#define DataUnit unsigned char
//#define CROP_MALLOC(A,B) malloc(A)
//#define CROP_FREE(A,B) free(A)

//----------------------------------------------------------------------------
// ll.h                                                                  
//----------------------------------------------------------------------------


//## package Buffer 


//## class ll 
class ll  {


////    Constructors and destructors    ////
public :
    
    //## operation ll() 
    ll();
    
    //## auto_generated 
    ~ll();


////    Operations    ////
public :
    
    //## operation addNode(DataUnit *) 
    void addNode(unsigned char * p_dataUnit);
    
    //## operation init_ll(ll **) 
    void init_ll(ll ** pllHead);
    
    //## operation printll() 
    void printll();
    
    //## operation removeNode() 
    unsigned char * removeNode();


////    Attributes    ////
protected :
    
    unsigned char * myDataUnit;		//## attribute myDataUnit 
    
    ll * pNext;		//## attribute pNext 
    

};


#endif  
/*********************************************************************
	File Path	: MAC/MAC/ll.h
*********************************************************************/


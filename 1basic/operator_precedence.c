#include <stdio.h>

int main(void)
{
	char temp1 = 1, temp2=2;
	char m, *p=&temp1; //e.
	m = *p++;   // m=*p=1; ++p, thus p now pointing to temp2 instead temp1
	p=&temp1;
	m = *++p;	// ++p, m=*p; thus p=&temp2, and m=2
	p=&temp1;
	m = ++*p; 	// char u=*p; m=++u; p value is untouched, temp1=2
	p=&temp1;
	temp1=5;
	m = (*p)++; // m = *p;
	return 0;
}

/*
=====================================================================================================
Precedence	 Operator	 			Description	 								Associativity
=====================================================================================================
1				::	 				Scope resolution	 						Left-to-right
-------------------------------------------------------------------------------
2				++   --	 			Suffix/postfix increment and decrement
				()	 				Function call
				[]	 				Array subscripting
				.	 				Element selection by reference
				->	 				Element selection through pointer
---------------------------------------------------------------------------------------------------- 
3				++   --	 			Prefix increment and decrement	 			Right-to-left
				+   −	 			Unary plus and minus
				!   ~	 			Logical NOT and bitwise NOT
				(type)	 			Type cast
				*	 				Indirection (dereference)
				&	 				Address-of
				sizeof	 			Size-of
				new, new[]			Dynamic memory allocation
				delete, delete[]	Dynamic memory deallocation
---------------------------------------------------------------------------------------------------- 
4				.*   ->*			Pointer to member	 						Left-to-right
-------------------------------------------------------------------------------- 
5				*   /   %			Multiplication, division, and remainder
-------------------------------------------------------------------------------- 
6				+   −	 			Addition and subtraction
-------------------------------------------------------------------------------- 
7				<<   >>	 			Bitwise left shift and right shift
-------------------------------------------------------------------------------- 
8				<   <=	 			For relational operators < and ≤ respectively
				> 	>=	 			For relational operators > and ≥ respectively
-------------------------------------------------------------------------------- 
9				==   !=	 			For relational = and ≠ respectively
-------------------------------------------------------------------------------- 
10				&	 				Bitwise AND
-------------------------------------------------------------------------------- 
11				^	 				Bitwise XOR (exclusive or)
-------------------------------------------------------------------------------- 
12				|	 				Bitwise OR (inclusive or)
-------------------------------------------------------------------------------- 
13				&&	 				Logical AND
-------------------------------------------------------------------------------- 
14				||	 				Logical OR
---------------------------------------------------------------------------------------------------- 
15				?:	 				Ternary conditional[1]	 					Right-to-left
				=	 				Direct assignment (provided by default for C++ classes)
				+=   −=	 			Assignment by sum and difference
				*=   /=   %=		Assignment by product, quotient, and remainder
				<<=   >>=	 		Assignment by bitwise left shift and right shift
				&=   ^=   |=		Assignment by bitwise AND, XOR, and OR
-------------------------------------------------------------------------------- 
16				throw	 			Throw operator (for exceptions)
---------------------------------------------------------------------------------------------------- 
17				,	 				Comma	 									Left-to-right
---------------------------------------------------------------------------------------------------- 

 */

/* 
machine code

m = *p++;   // m=*p=1; ++p, thus p now pointing to temp2 instead temp1
=> 0x08048400 <+20>:    mov    -0x4(%ebp),%eax
   0x08048403 <+23>:    movzbl (%eax),%eax
   0x08048406 <+26>:    mov    %al,-0x5(%ebp)
   0x08048409 <+29>:    addl   $0x1,-0x4(%ebp)


#include<stdio.h>

main()
{
	printf("The color: %s\n", "blue");
	printf("First number: %d\n", 12345);
	printf("Second number: %04d\n", 25);
	printf("Third number: %i\n", 1234);
	printf("Float number: %3.2f\n", 3.14159);
	printf("Hexadecimal: %x\n", 255);
	printf("Octal: %o\n", 255);
	printf("Unsigned value: %u\n", 150);
	printf("Just print the percentage sign %%\n");
	printf("================================================================================\n\n");
	printf("%-15s:%s:\n", "<%s>", "Hello, world!");
	printf("%-15s:%15s:\n", "<%15s>", "Hello, world!");
	printf("%-15s:%.10s:\n", "<%.10s>", "Hello, world!");
	printf("%-15s:%-10s:\n", "<%-10s>", "Hello, world!");
	printf("%-15s:%-15s:\n", "<%-15s>", "Hello, world!");
	/// .15 print max only 15 char
	printf("%-15s:%.15s:\n", "<%.15s>", "Hello, world!");
	/// .10 print max only 10 char, the rest is white space (right adjusted)
	printf("%-15s:%15.10s:\n", "<%15.10s>", "Hello, world!");
	/// .10 print max only 10 char, the rest is white space (left adjusted)
	printf("%-15s: %-15.10s:\n", "<%-15.10s>","Hello, world!");  
	printf("================================================================================\n\n");
	printf ("Characters: %c %c \n", 'a', 65);
	printf ("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
	printf ("floats: %4.2f %+.0e %E \n", 3.1416, 3.1416, 3.1416);
	printf ("Width trick: %*d \n", 5, 10);
	printf ("Decimals: %d %ld\n", 1977, 650000L);
	printf ("Preceding with blanks: %10d \n", 1977);
	printf ("Preceding with zeros: %010d \n", 1977);
}

/* 
result:
The color: blue
First number: 12345
Second number: 0025
Third number: 1234
Float number: 3.14
Hexadecimal: ff
Octal: 377
Unsigned value: 150
Just print the percentage sign %
================================================================================

<%s>           :Hello, world!:
<%15s>         :  Hello, world!:
<%.10s>        :Hello, wor:
<%-10s>        :Hello, world!:
<%-15s>        :Hello, world!  :
<%.15s>        :Hello, world!:
<%15.10s>      :     Hello, wor:
<%-15.10s>     : Hello, wor     :
================================================================================

Characters: a A 
Some different radices: 100 64 144 0x64 0144 
floats: 3.14 +3e+00 3.141600E+00 
Width trick:    10 
Decimals: 1977 650000
Preceding with blanks:       1977 
Preceding with zeros: 0000001977 
*/

/* reference:
A format specifier follows this prototype: 
%[flags][width][.precision][length]specifier 

================================================================================
specifier	Output	Example
================================================================================
d or i	Signed decimal integer	392
u	Unsigned decimal integer	7235
o	Unsigned octal	610
x	Unsigned hexadecimal integer	7fa
X	Unsigned hexadecimal integer (uppercase)	7FA
f	Decimal floating point, lowercase	392.65
F	Decimal floating point, uppercase	392.65
e	Scientific notation (mantissa/exponent), lowercase	3.9265e+2
E	Scientific notation (mantissa/exponent), uppercase	3.9265E+2
g	Use the shortest representation: %e or %f	392.65
G	Use the shortest representation: %E or %F	392.65
a	Hexadecimal floating point, lowercase	-0xc.90fep-2
A	Hexadecimal floating point, uppercase	-0XC.90FEP-2
c	Character	a
s	String of characters	sample
p	Pointer address	b8000000
n	Nothing printed.
The corresponding argument must be a pointer to a signed int.
The number of characters written so far is stored in the pointed location.	
%	A % followed by another % character will write a single % to the stream.	%


================================================================================
flags	description
================================================================================
-		Left-justify within the given field width; Right justification is the 
		default (see width sub-specifier).
--------------------------------------------------------------------------------
+		Forces to preceed the result with a plus or minus sign (+ or -) even 
		for positive numbers. By default, only negative numbers are preceded 
		with a - sign.
--------------------------------------------------------------------------------
(space)	If no sign is going to be written, a blank space is inserted before the 
		value.
--------------------------------------------------------------------------------
#		Used with o, x or X specifiers the value is preceeded with 0, 0x or 0X 
		respectively for values different than zero.
		Used with a, A, e, E, f, F, g or G it forces the written output to 
		contain a decimal point even if no more digits follow. By default, if 
		no digits follow, no decimal point is written.
--------------------------------------------------------------------------------
0		Left-pads the number with zeroes (0) instead of spaces when padding is 
		specified (see width sub-specifier).
--------------------------------------------------------------------------------

================================================================================
width		description
================================================================================
(number)	Minimum number of characters to be printed. If the value to be 
			printed is shorter than this number, the result is padded with 
			blank spaces.  The value is not truncated even if the result is 
			larger.
--------------------------------------------------------------------------------
*           The width is not specified in the format string, but as an 
            additional integer value argument preceding the argument that has 
            to be formatted.
--------------------------------------------------------------------------------


================================================================================
.precision	description
================================================================================
.number		For integer specifiers (d, i, o, u, x, X): precision specifies the 
			minimum number of digits to be written. If the value to be written 
			is shorter than this number, the result is padded with leading 
			zeros. The value is not truncated even if the result is longer. A 
			precision of 0 means that no character is written for the value 0.
			For a, A, e, E, f and F specifiers: this is the number of digits to be printed 
			after the decimal point (by default, this is 6).
			For g and G specifiers: This is the maximum number of significant 
			digits to be printed.
			For s: this is the maximum number of characters to be printed. By 
			default all characters are printed until the ending null character 
			is encountered.
			If the period is specified without an explicit value for precision, 
			0 is assumed.
--------------------------------------------------------------------------------
.*			The precision is not specified in the format string, but as an 
			additional integer value argument preceding the argument that has 
			to be formatted.
--------------------------------------------------------------------------------


============================================================================================================
specifiers
============================================================================================================
length	d i				u o x X					f F e E g G a A		c		s			p		n
------------------------------------------------------------------------------------------------------------
(none)	int				unsigned int			double				int		char*		void*	int*
hh		signed char		unsigned char															signed char*
h		short int		unsigned short int									short int*
l		long int		unsigned long int							wint_t	wchar_t*			long int*
ll		long long int	unsigned long long int													long long int*
j		intmax_t		uintmax_t																intmax_t*
z		size_t			size_t																	size_t*
t		ptrdiff_t		ptrdiff_t																ptrdiff_t*
L												long double			
------------------------------------------------------------------------------------------------------------

*/

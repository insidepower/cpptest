#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//#define DEBUG

#ifdef DEBUG
#define FPRINTF(A,B) 		fprintf(fp_dst, "%c%c=%s%s\n", ptr[0], ptr[1], A, B)
#define FPRINTF_R(A,B) 	    \
		fprintf(fp_dst_reversed, "%c%c=%s%s\n", ptr[0], ptr[1], A, B)
#else
#define FPRINTF(A,B) 		fprintf(fp_dst, "%s%s\n", A, B)
#define FPRINTF_R(A,B) 	    fprintf(fp_dst_reversed, "%s%s\n", A, B)
#endif

/// hex to binary conversion array
char ar_hex_to_bin[16][5] = {
"0000",
"0001",
"0010",
"0011",
"0100",
"0101",
"0110",
"0111",
"1000",
"1001",
"1010",
"1011",
"1100",
"1101",
"1110",
"1111",
};

/// hex to reversed binary conversion array
char ar_hex_to_bin_r[16][5] = {
"0000",
"1000",
"0100",
"1100",
"0010",
"1010",
"0110",
"1110",
"0001",
"1001",
"0101",
"1101",
"0011",
"1011",
"0111",
"1111",
};


/// convert hexadecimal to 4 bit binary
int conv_hex_bin(char hex)
{
	switch(hex){
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'A': return 10;
		case 'B': return 11;
		case 'C': return 12;
		case 'D': return 13;
		case 'E': return 14;
		case 'F': return 15;
		default:
			printf("Error! char=%c", hex);
			exit(1);
	}
}

int main(void)
{
	/// declare variables\n
	FILE * fp_src = NULL;
	FILE * fp_dst = NULL;
	FILE * fp_dst_reversed = NULL;

	/// open file\n
	fp_src = fopen("chiprom_posedge.vhd", "r");
	fp_dst = fopen("binary.txt", "w");
	fp_dst_reversed = fopen("binary_reversed.txt", "w");

	/// convert the hex to binary in each line\n
#define LINE_SIZE 	(100)
	char line[LINE_SIZE];
	char * ptr = NULL;
	while (!feof(fp_src)) {
		fgets(line, LINE_SIZE, fp_src);
		//printf("%s", line);

		/// .get the pattern of x" which mark the beginning of data\n
		ptr = strstr(line, "x\"");
		int first_hex = 0;
		int second_hex = 0;
		while ( NULL != ptr){
			/// ..increment by 2 to ignore x", and point to first hex char
			ptr+=2;
			//printf("%c%c", ptr[0], ptr[1]);
			first_hex = conv_hex_bin(ptr[0]);
			second_hex = conv_hex_bin(ptr[1]);
			//printf("=%s ", ar_hex_to_bin[first_hex]);
			//printf("%s, ", ar_hex_to_bin[second_hex]);
			//printf("=%s%s\n",ar_hex_to_bin_r[first_hex], ar_hex_to_bin_r[second_hex]);
			FPRINTF(ar_hex_to_bin[first_hex], ar_hex_to_bin[second_hex]);
			//FPRINTF_R(ar_hex_to_bin_r[first_hex], ar_hex_to_bin_r[second_hex]);
			/// e.g. A2=1010 0010, (reversed=0100 0101= r-second hex,r-first hex)
			FPRINTF_R(ar_hex_to_bin_r[second_hex], ar_hex_to_bin_r[first_hex]);

			/// ..increment to next pointer after second hex char
			ptr++;
			ptr = strstr(ptr, "x\"");
		}
	}

	/// close file\n
	fclose(fp_src);
	fclose(fp_dst);
	fclose(fp_dst_reversed);

	printf("program ended\n");

	return 0;
}

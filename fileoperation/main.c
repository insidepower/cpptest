#include <stdio.h>

int main(void){
	FILE * fp = fopen("test.txt", "wb");
	int i=0;
	char write = 0x1;
	for (i=0; i<8; i++){
		fwrite(&write, sizeof(char), 1, fp);
		write++;
	}
	fclose(fp);

	fp = fopen("test.txt", "rb");
	char read = 0;
	printf("reading: ");
	for (i=0; i<8; i++){
		fread(&read, sizeof(char), 1, fp);
		printf("%02x ", read);
	}
	printf("\n");
	fclose(fp);

	fp = fopen("test.txt", "rb");
	fseek(fp, -5, SEEK_END);
	printf("reading2: ");
	for (i=0; i<5; i++){
		fread(&read, sizeof(char), 1, fp);
		printf("%02x ", read);
	}
	printf("\n");
	fclose(fp);
	return 0;
}

/* result:
reading: 01 02 03 04 05 06 07 08
reading2: 04 05 06 07 08
 */

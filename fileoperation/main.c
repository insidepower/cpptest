#include <stdio.h>

struct GPS {
	double latitude;
	double longitude;
};

void strcmp_func(void)
{
	unsigned char ind_data[13] = {
		0x9d, 0x11, 0x02, 0x23, 0x10, 
		0x00, 0x24, 0x00, 0x00, 0x58, 
		0, 0, 0};
	unsigned char eng_data[13] = {
		0x9d, 0x11, 0x02, 0x23, 0x10, 
		0x00, 0x25, 0x00, 0x00, 0x58, 
		0, 0, 0};

	unsigned char * p_ind = ind_data;
	unsigned char * p_eng = eng_data;

	printf("ind: %02x %02x %02x\n", 
			*(p_ind+4),
			*(p_ind+4+1),
			*(p_ind+4+2));
	
	printf("eng: %02x %02x %02x\n", 
			*(p_eng+4),
			*(p_eng+4+1),
			*(p_eng+4+2));

	if (memcmp(p_ind+4, p_eng+4, 3)==0){
		printf("both are same\n");
	}else{
		printf("both are not same\n");
	}
}

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
	int fsize = ftell(fp);
	printf("file size is: %d\n", fsize);
	fclose(fp);

	fp = fopen("IndData2.txt", "rb");
	//int length = -(219+17-2);
	int data_length = 219;
	int length = -(data_length+sizeof(struct GPS)+1-2);
	fseek(fp, length, SEEK_END);
	char time[5];
	printf("reading3: ");
	for (i=0; i<5; i++){
		fread(&time[i], sizeof(char), 1, fp);
	}
	printf("%02x %02x %02x %02x %02x\n",
			time[0],
			time[1],
			time[2],
			time[3],
			time[4]);
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	printf("file size is: %d\n", fsize);
	fclose(fp);

	fp = fopen("EngData1.txt", "rb");
	data_length = 152;
	int eng_date_start = -(data_length-2);
	FILE * temp_fp = fp;
	FILE * temp_fp_new = fopen("EngData1.txt", "rb");
	char time3[5];
	char time2[5];
	fseek(fp, eng_date_start, SEEK_END);
	printf("reading EngData2: fp=%p\n", fp);
	printf("b4 readin: fp=%p, ftell_fp=%ld, ftell_temp=%ld"
			", ftell_new=%ld\n",
			fp, ftell(fp), ftell(temp_fp), ftell(temp_fp_new));
	for (i=0; i<5; i++){
		fread(&time[i], sizeof(char), 1, fp);
	}
	for(i=0; i<5; i++){
		fread(&time3[i], sizeof(char), 1, temp_fp_new);
		printf("%02x ", time[i]);
	}
	printf("after readin: fp=%p, ftell_fp=%ld, ftell_temp=%ld"
			", ftell_new=%ld\n",
			fp, ftell(fp), ftell(temp_fp), ftell(temp_fp_new));
	printf("%02x %02x %02x %02x %02x\n",
			time[0],
			time[1],
			time[2],
			time[3],
			time[4]);

	/// testing if we store the fp to another var (temp_fp)
	/// will it still point to the correct location
	/// if the origin fp already move to another place
	for (i=0; i<5; i++){
		fread(&time2[i], sizeof(char), 1, temp_fp);
	}
	printf("after readin2: fp=%p, ftell_fp=%ld, ftell_temp=%ld"
			", ftell_new=%ld\n",
			fp, ftell(fp), ftell(temp_fp), ftell(temp_fp_new));
	printf("time2: %02x %02x %02x %02x %02x\n",
			time2[0],
			time2[1],
			time2[2],
			time2[3],
			time2[4]);

	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	printf("file size is: %d\n", fsize);
	fclose(fp);

	strcmp_func();
	return 0;
}

/* result:
reading: 01 02 03 04 05 06 07 08
reading2: 04 05 06 07 08
reading3: 02 23 09 08 59
 */

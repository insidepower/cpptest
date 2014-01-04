/*============================================================================
  ==  @ icon.c @
  ==
  ==  DESC: To decode the xxx.ico format and read the data for openGL stencil
  == 		use. Design to work for 32x32 icon. And only read one image.
  ==  USAGE:
  ==  INPUTS:
  ==  OUTPUTS:
  ==  RETURN:
  ==  IMP NOTE: this program assume little endian byte order
  ============================================================================*/
#include <stdio.h>
#include <stdlib.h>     /* exit, EXIT_FAILURE */


/*===========================================================================
  ==  global variable and struct declarations
  ===========================================================================*/
typedef struct icon_entry {
	char 	width;			// width in pixels
	char 	height;			// height in pixels
	char	colorCount;		// number of color palette used. 0 if none is used.
	char 	rsvd;			// reserved, not used (value=0)
	short 	plane;			// color planes (0 or 1)
	short 	bitPerPixel;
	int		sizeInByte;
	int		offset;			// offset from beginning of this file, the idReserved data of ico_spec
}icon_entry;

typedef struct ico_spec {
	short 	idReserved; 	// Reserved (value=0)
	short 	idType;			// Resource Type (icon=1)
	short 	idCount;		// How many images stored?
	//icon_entry	* pIcon;	// entry to each icon/image content
}ico_spec;

ico_spec my_spec;
icon_entry my_entry;

/*===========================================================================
  == Functions
  ===========================================================================*/
void readAllData(FILE *fp){
	unsigned char c = 0;
	int numByteRead = 0;
	// fgetc is not suitable as it is returning the ascii char, 
	// instead of the intended binary value
	//while(c=fgetc(fp) != EOF){
	do {
		numByteRead = fread(&c, sizeof(char), 1, fp);
		printf("%02x ", c);
	} while (numByteRead != 0);
	/// fread return 0 if end of file reached. 
	/// but should be checked with feof or ferror to make sure
	printf("\n");

	if ( 1==feof(fp)) {
		printf("file read finished!\n");
	} else {
		printf("file error occurred!\n");
		exit(EXIT_FAILURE);
	}
}

void typeSizeChecking(void){
	if ( sizeof(short)!=2){
		printf("sizeof of short is not 2!!!\n");
		exit(EXIT_FAILURE);
	}

	if ( sizeof(int)!=4){
		printf("sizeof of int is not 4!!!\n");
		exit(EXIT_FAILURE);
	}

	if ( sizeof(char)!=1){
		printf("sizeof of char is not 1!!!\n");
		exit(EXIT_FAILURE);
	}

}

void checkIcoValid(){
	if (1!=my_spec.idType){
		printf("not ICO file format. Abandon decoding!\n");
		exit(EXIT_FAILURE);
	}
}

void readIcoHeader(FILE *fp){
	fread(&my_spec.idReserved, sizeof(my_spec.idReserved), 1, fp);
	fread(&my_spec.idType, sizeof(my_spec.idType), 1, fp);
	fread(&my_spec.idCount, sizeof(my_spec.idCount), 1, fp);
	fread(&my_entry.width, sizeof(my_entry.width), 1, fp);
	fread(&my_entry.height, sizeof(my_entry.height), 1, fp);
	fread(&my_entry.colorCount, sizeof(my_entry.colorCount), 1, fp);
	fread(&my_entry.rsvd, sizeof(my_entry.rsvd), 1, fp);
	fread(&my_entry.plane, sizeof(my_entry.plane), 1, fp);
	fread(&my_entry.bitPerPixel, sizeof(my_entry.bitPerPixel), 1, fp);
	fread(&my_entry.sizeInByte, sizeof(my_entry.sizeInByte), 1, fp);
	fread(&my_entry.offset, sizeof(my_entry.offset), 1, fp);

	printf("ico_spec.idReserved=%d\n", my_spec.idReserved);
	printf("ico_spec.idType=%d\n", my_spec.idType);
	printf("ico_spec.idCount=%d\n", my_spec.idCount);
	printf("my_entry.width=%d\n", my_entry.width);
	printf("my_entry.height=%d\n", my_entry.height);
	printf("my_entry.colorCount=%d\n", my_entry.colorCount);
	printf("my_entry.rsvd=%d\n", my_entry.rsvd);
	printf("my_entry.plane=%d\n", my_entry.plane);
	printf("my_entry.bitPerPixel=%d\n", my_entry.bitPerPixel);
	printf("my_entry.sizeInByte=%d\n", my_entry.sizeInByte);
	printf("my_entry.offset=%d\n", my_entry.offset);
}

void readFirstIcoEntry(FILE *fp){
	int imgSize = my_entry.sizeInByte - my_entry.offset;
	int * pData[32];
	int numByteRead = 0;

	/// offset the file pointer to where the icon data start
	//fp = fp + my_entry.offset;
	//do {
	//	numByteRead = fread(&c, 4, 32, fp);
	//	printf("%02x ", c);
	//} while (numByteRead != 0);
	FILE * pTemp = fp;
	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	printf("size = %lu; size-offset=%lu\n", size, (size-my_entry.offset));
}

int main(void){
	//FILE * fp = fopen("knxy.ico", "rb");
	FILE * fp = fopen("test2.ico", "rb");

	typeSizeChecking();

/*
	/// test read and type size checking
	{
		readAllData(fp);

		/// rewind to starting byte
		rewind(fp);
	}
*/
	readIcoHeader(fp);
	readFirstIcoEntry(fp);

	fclose(fp);

	return 0;
}

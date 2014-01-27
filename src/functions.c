/****************************************************
	Autor: Feng Wen
	Email: fengwen@usc.edu
	Date: 01/25/2014
*****************************************************/
#include "hw1.h"

unsigned char *base64_dec_table = NULL; //declare base64 decoding table pointer
static char base64_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/', '='}; //declare and initialize base64 encodeing table

void hexdumpStdin(){
	unsigned char ch = 0; // For every byte inputed
	int count = 0;        // counter
	char buff[17];        // For text that will be printed on the right column
	while(read(0, &ch, sizeof(ch))){		
		
		/*
			print one line for every 16 bytes
		*/
		if(count % 16 == 0){
			
			if(count != 0){
				buff[16] = 0;
				puts(buff);			
			}	
			printf("%06x: ", count);
		}
	
		printf("%02x ", ch);
		
		//Converting non-printable character into '.' or '~'
		if(ch <= 0x1f || ch == 0x7f){
			ch = '.';
		}
		else{ 
			if(ch >= 0x80){
				ch = '~';
			}
			
		}
		
		buff[count % 16] = ch;
		count++;
		if(count % 8 == 0){
			putchar(' ');		
		}

		
	}
	
	//print '--' for the last line
	if(count != 0){
		while(count % 16 != 0){		
			buff[count % 16] = ' ';
			printf("-- ");	
			count++;
			if(count % 8 == 0){
				putchar(' ');
			}				
		}
		buff[16] = 0;
		printf("%s\n", buff);
	}
}
void encBase64Stdin(){
	unsigned char buff[3] = {0, 0, 0}; //For every 3 bytes that will be encoded
	unsigned char ch = 0;			   //For every byte inputed
	/*
		b0, b1, b2, b3 are corresponding base64 characters
	*/
	unsigned char b0 = 0;
	unsigned char b1 = 0;
	unsigned char b2 = 0;
	unsigned char b3 = 0;
	int i = 0, count = 0;
	
	
	while(read(0, &ch, sizeof(ch))){		
		buff[1] = buff[2] = buff[0] = 0;
		buff[0] = ch;
		i = 1;
		count++;
		
		/*
			Put every 3 bytes into buff
		*/
		do{
			if(read(0, &ch, sizeof(ch)) == 0)
				break;
			buff[i] = ch;
			i++;
			count++;
		}while(i < 3);
		
		/*
			Encoding bytes in buff into base64 characters
		*/
		b0 = (buff[0] & 0xfc) >> 2;
		b1 = ((buff[0] & 0x03) << 4) | (buff[1] >> 4);
		b2 = ((buff[1] & 0x0f) << 2) | ((buff[2] & 0xc0) >> 6);
		b3 = buff[2] & 0x3f;
		
		/*
			Solving Endgame
		*/
		if(i == 1){
			b2 = b3 = 64;
		}
		
		if(i == 2){
			b3 = 64;
		}
		
		putchar(base64_table[b0]);
		putchar(base64_table[b1]);
		putchar(base64_table[b2]);
		putchar(base64_table[b3]);
		
		if(count % 48 == 0){
			printf("\n");
		}
		
		if(i != 3){
			break;
		}
		
	}
	if(count > 0 && count % 48 != 0){
		printf("\n");
	}
	
}
void decBase64Stdin(){
	uint32_t buff = 0;
	uint32_t bf[4] = {0, 0, 0, 0}; //For every four base64 characters that will be encoded
	unsigned char ch = 0; // For every byte that inputed
	/*
		b0, b1, b2 are bytes that has been encoded.
	*/
	unsigned char b0 = 0; 
	unsigned char b1 = 0;
	unsigned char b2 = 0;
	int i = 0, count = 0;
	
	base64_dec_table = generateEncTable(); //Generate base64 decoding table
	if(!base64_dec_table){
		printf("base64 encodeing table created error\n");
		return;
	}
	if(read(0, &ch, sizeof(unsigned char)) <= 0)
		return;
	while(1){
		bf[0] = bf[1] = bf[2] = bf[3] = 0;
		do{		
			// Check base64 Character validity
			if(!isValidChar(ch)){
				printf("Invalid base64 character in stdin!\n");
				return;
			}
			
			// Filter newline sign
			for(; ch == '\n'; count++){
				if(read(0, &ch, sizeof(unsigned char)) <= 0){
					break;
				}
			}
			if(ch != '=' && ch != '\n'){
				bf[i] = base64_dec_table[ch - DEC_TABLE_OFFSET];
				i++;
			}
			else{
				break;
			}
			if(read(0, &ch, sizeof(unsigned char)) <= 0)
				break;
		}while(i < 4);
		buff = (bf[0] << 24) + (bf[1] << 16) + (bf[2] << 8) + bf[3];
		
		// Decode base64 characters into original data
		if(i == 0) break;
		b0 = (buff & 0x3f000000) >> 22 | (buff & 0x00300000) >> 20;
		b1 = (buff & 0x000f0000) >> 12 | (buff & 0x00003c00) >> 10;
		b2 = (buff & 0x00000300) >> 2 | (buff & 0x0000003f);
		putchar(b0);
		if(i == 2) break;
		putchar(b1);
		if(i == 3) break;
		putchar(b2);
		i = 0;
	}
	
	

	free(base64_dec_table);

}
void hexdumpFile(char *fileName){
	FILE *ifp = NULL;
	char *mode = "r";
	unsigned char ch = 0;
	ifp = fopen(fileName, mode);
	int count = 0;
	char buff[17];
	
	if(ifp == NULL){
		fprintf(stderr, "Can't open %s\n", fileName);
		return;	
	}

	while(!feof(ifp)){	
		if(count % 16 == 0){	
			if(count != 0){
				buff[16] = 0;
				printf("%s\n", buff);			
			}	
			printf("%06x: ", count);
		}
		ch = fgetc(ifp);
		if(feof(ifp)){
			break;		
		}
		printf("%02x ", ch);
		if(ch <= 0x1f || ch == 0x7f){
			ch = '.';
		}
		else{ 
			if(ch >= 0x80){
				ch = '~';
			}		
		}		
		buff[count % 16] = ch;
		count++;
		if(count % 8 == 0){
			putchar(' ');		
		}
		
	}

	if(count != 0){
		while(count % 16 != 0){		
			buff[count % 16] = ' ';
			printf("-- ");	
			count++;
			if(count % 8 == 0){
				putchar(' ');
			}				
		}
		buff[16] = 0;
		printf("%s\n", buff);
	}

	fclose(ifp);

}


void encBase64File(char *fileName){
	
	FILE *ifp = NULL;
	char *mode = "r";
	ifp = fopen(fileName, mode);
	int count = 0;
	unsigned char buff[3];
	unsigned char b0 = 0;
	unsigned char b1 = 0;
	unsigned char b2 = 0;
	unsigned char b3 = 0;
	int length = 0;
	
	/*
		Get length of the file
	*/
	fseek(ifp, 0, SEEK_END);
	length = ftell(ifp);
	fseek(ifp, 0, SEEK_SET);
	while(count < length){
		buff[0] = buff[1] = buff[2] = 0;
		fread(buff, sizeof(buff)/sizeof(char), 1, ifp);	
		count += 3;
		b0 = (buff[0] & 0xfc) >> 2;
		b1 = ((buff[0] & 0x03) << 4) | (buff[1] >> 4);
		b2 = ((buff[1] & 0x0f) << 2) | ((buff[2] & 0xc0) >> 6);
		b3 = buff[2] & 0x3f;
		if(count - length == 2){
			b2 = b3 = 64;
		}
		if(count - length == 1){
			b3 = 64;
		}		
		putchar(base64_table[b0]);
		putchar(base64_table[b1]);
		putchar(base64_table[b2]);
		putchar(base64_table[b3]);
		if(count % 48 == 0 && count < length){
			printf("\n");
		}	
	}

	if(count){
		printf("\n");
	}
}
void decBase64File(char *fileName){
	FILE *ifp = NULL;
	char *mode = "r";
	ifp = fopen(fileName, mode);
	int count = 0;
	static int endComing = 0;
	unsigned char buff[4];
	unsigned char b0 = 0;
	unsigned char b1 = 0;
	unsigned char b2 = 0;	
	int length = 0, i = 0;
	unsigned char ch = 0;
	fseek(ifp, 0, SEEK_END);
	length = ftell(ifp);
	if(length == 0){
		fprintf(stderr, "NULL Document Error!!!");
	}
	fseek(ifp, 0, SEEK_SET);
	base64_dec_table = generateEncTable();
	if(!base64_dec_table){
		printf("insufficient Memory!\n");
		return;
	}
	for(; count < length; i = 0){
		buff[0] = buff[1] = buff[2] = buff[3] = 0;
		
		for(; i < 4 && count < length;){
			ch = fgetc(ifp);
			count++;
			
			if(!isValidChar(ch)){
				printf("%s has invalid base64 character!\n", fileName);
				return;
			}
			for(; ch == '\n' && count < length; ch = fgetc(ifp), count++);
			if(ch != '=' && ch != '\n'){
				buff[i] = base64_dec_table[ch - DEC_TABLE_OFFSET];
				i++;
			}
			else{
				endComing = i;
				break;
			}
			 
		}
		
		if(i == 0) break;
		b0 = (buff[0] << 2) | (buff[1] >> 4);
		b1 = (buff[1] << 4) | (buff[2] >> 2);
		b2 = (buff[2] << 6) | (buff[3]);
		putchar(b0);
		if(endComing == 2) break;
		putchar(b1);
		if(endComing == 3) break;
		putchar(b2);
	}
	
	

	free(base64_dec_table);

}

int isValidChar(char ch){
	if((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') 
		|| (ch >= 'A' && ch <= 'Z') || ch == '+' || ch == '/' || ch == '\n' || ch == '='){
		return 1;
	}
	else{
		return 0;	
	}
}

unsigned char * generateEncTable(){
	int i = 0;
	unsigned char *encTableP = (unsigned char*) calloc(DEC_TABLE_LENGTH, sizeof(unsigned char));
	if(encTableP != NULL){
		for(; i < ENC_TABLE_LENGTH; i++){
			encTableP[base64_table[i]-DEC_TABLE_OFFSET] = i; 
		}
		
	}
	return encTableP;
}


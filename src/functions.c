#include "hw1.h"
void hexdumpStdin(){
	unsigned char ch = 0;
	int count = 0;
	char buff[17];
	while(read(0, &ch, sizeof(ch))){
		if(ch == EOF) 
			break;		
		if(count % 16 == 0){
			
			if(count != 0){
				buff[16] = 0;
				puts(buff);
				putchar('\n');			
			}	
			printf("%06x: ", count);
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
			if(count % 8 == 0){
				putchar(' ');
			}		
			buff[count % 16] = ' ';
			printf("-- ");
					
			count++;
		
		}
		buff[16] = 0;
		printf(" %s\n", buff);
	}
}
void encBase64Stdin(){
	printf("enc-base64Stdin()\n");
}
void decBase64Stdin(){
	printf("dec-base64Stdin()\n");
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
			if(count % 8 == 0){
				putchar(' ');
			}		
			buff[count % 16] = ' ';
			printf("-- ");				
			count++;	
		}
		buff[16] = 0;
		printf(" %s\n", buff);
	}

	fclose(ifp);

}
void encBase64File(char *fileName){
	static char base64_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
	FILE *ifp = NULL;
	char *mode = "r";
	ifp = fopen(fileName, mode);
	int count = 0;
	unsigned char buff[3];
	unsigned char b0 = 0;
	unsigned char b1 = 0;
	unsigned char b2 = 0;
	unsigned char b3 = 0;
	printf("encBase64File()\n");
	printf("File Name: %s\n", fileName);

	while(!feof(ifp)){
		buff[0] = buff[1] = buff[2] = 0;		
		fread(buff, sizeof(buff)/sizeof(char), 1, ifp);
		count++;
		b0 = (buff[0] & 0xfc) >> 2;
		b1 = ((buff[0] & 0x03) << 4) & (buff[1] >> 4);
		b2 = ((buff[1] & 0x0f) << 2) & ((buff[2] && 0xc0) >> 6);
		b3 = buff[2] & 0x3f;
		if(!buff[1]){
			b2 = b3 = '=';
		}
		if(!buff[2]){
			b3 = '=';
		}		
		putchar(base64_table[b0]);
		putchar(base64_table[b1]);
		putchar(base64_table[b2]);
		putchar(base64_table[b3]);
		if(count % 16)
			printf("\n");
	}
}
void decBase64File(char *fileName){
	printf("decBase64File()\n");
	printf("File Name: %s\n", fileName);
}

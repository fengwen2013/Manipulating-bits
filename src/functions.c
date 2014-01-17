#include "hw1.h"
void hexdumpStdin(){
	unsigned char ch = 0;
	int count = 0;
	char buff[17];
	while(read(0, &ch, sizeof(ch))){
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
	
	fclose(ifp);

}
void encBase64File(char *fileName){
	printf("encBase64File()\n");
	printf("File Name: %s\n", fileName);
}
void decBase64File(char *fileName){
	printf("decBase64File()\n");
	printf("File Name: %s\n", fileName);
}

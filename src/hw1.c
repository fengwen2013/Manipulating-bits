/****************************************************
	Autor: Feng Wen
	Email: fengwen@usc.edu
	Date: 01/25/2014
*****************************************************/
#include "hw1.h"

int main(int argc, char *argv[]){
	switch(argc){
	case 1: printf("Error: Lack of argument(s) (can be hexdump | enc-base64 | dec-base64)\n"); break;
	case 2: oneArgument(argv); break;
	case 3: twoArguments(argv); break;
	default: printf("Error: Too many arguments (the number of arguments should be less than or equal to 2)\n");
	}		
	return 0;
}

/*
	Handle the situation where user only input one argument, display error information when
	invalid argument is inputed
*/
void oneArgument(char *argv[]){
	if(strcmp(argv[1], "hexdump") == 0){
		hexdumpStdin();	
	}
	else{
		if(strcmp(argv[1], "enc-base64") == 0){
			encBase64Stdin();	
		}
		else{
			if(strcmp(argv[1], "dec-base64") == 0){
				decBase64Stdin();
			}
			else{
				printf("Error: the first argument should be hexdump | enc-base64 | dec-base64)\n");
			}		
		}
	}
}

/*
	Handle the situation where user input two arguments, display error information when invalid 
	arguments are inputed or file doesn't exist 
*/
void twoArguments(char *argv[]){
	int funcFlag = 0;
	if(strcmp(argv[1], "hexdump") == 0){
		funcFlag = 1;
	}
	else{
		if(strcmp(argv[1], "enc-base64") == 0){
			funcFlag = 2;	
		}
		else{
			if(strcmp(argv[1], "dec-base64") == 0){
				funcFlag = 3;
			}
			else{
				printf("Error: the first argument should be hexdump | enc-base64 | dec-base64)\n");
				return;
			}		
		}
	}
	
	if(access(argv[2], F_OK) != -1){
		switch(funcFlag){
		case 1: hexdumpFile(argv[2]);break;
		case 2: encBase64File(argv[2]);break;
		case 3: decBase64File(argv[2]);break;
		}
	}
	else{
		printf("Error: this file doesn't exsit\n");	
	}
}


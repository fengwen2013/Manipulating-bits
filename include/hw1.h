#include "stdio.h"
#include "string.h"
#include "unistd.h"


#define HEXDUMP 1
#define ENCBASE64 2
#define DECBASE64 3

void hexdumpStdin();
void encBase64Stdin();
void decBase64Stdin();
void hexdumpFile(char *fileName);
void encBase64File(char *fileName);
void decBase64File(char *fileName);
void oneArgument();
void twoArguments();

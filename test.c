#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *b;
	BigInt *one = parseBigInt("1");
	BigInt *result;
	char *s = malloc(sizeof(char) * 20);
	for(int i = 214;i >= -20;--i){
		sprintf(s,"%d",i);
		b = parseBigInt(s);
		result = difBigInts(b,one);
		printBigInt(result);
		
		freeBigInt(result);
		freeBigInt(b);
	}
	return 0;
}

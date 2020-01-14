#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *big;
	BigInt *zero = parseBigInt("0");
	char *s = malloc(sizeof(char) * 20);
	int result;
	for(int i = 65536;i >= -10;--i){
		sprintf(s,"%d",i);
		big = parseBigInt(s);
		result = greaterThanBigInt(big,zero);
		if(!result){
			printf("int: %d BigInt: ",i);
			printBigInt(big);
		}
		freeBigInt(big);
	}
	free(s);
	
	return 0;
}

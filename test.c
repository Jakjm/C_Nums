#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *b = parseBigInt("-4");
	BigInt *e;
	BigInt *power;
	int i;
	char *str = malloc(sizeof(char)  * 25);
	for(i = 0;i < 20;++i){
		printf("-1 raised to %d: ",i);
		sprintf(str,"%d",i);
		e = parseBigInt(str);
		power = powerBigInts(b,e);
		printBigInt(power);
		freeBigInt(e);
		freeBigInt(power);
	}
	return 0;
}

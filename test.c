#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	int i, b;
	char *s = malloc(sizeof(char) * 50);
	BigInt *c, *a,*b = parseBigInt("20");
	for(i = 1;i < 21;++i){
		for(b = 0;b < 20;++b){
			sprintf(s,"%d",i);
			a = parseBigInt(s);
			c = quotientBigInts(b,a);
			printf("20 divided by %d = ",i);
			printBigInt(c);
			freeBigInt(a);
		}
	}
	return 0;
}

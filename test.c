#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	int b;
	char *s = malloc(sizeof(char) * 50);
	BigInt *c, *a,*z = parseBigInt("20");
	for(b = 0;b < 22;++b){
		sprintf(s,"%d",b);
		a = parseBigInt(s);
		c = quotientBigInts(z,a);
		printf("20 divided by %d = ",b);
		printBigInt(c);
		freeBigInt(a);
	}
	printf("0 divided by 0: ");
	printBigInt(quotientBigInts(parseBigInt("0"),parseBigInt("0")));
	return 0;
}

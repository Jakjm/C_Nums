#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *bigint = parseBigInt("1");
	BigInt *int2 = parseBigInt("2");
	BigInt *int3 = parseBigInt("3");
	printSpecs(difBigInts(difBigInts(int3,int2),bigint));
	return 0;
}

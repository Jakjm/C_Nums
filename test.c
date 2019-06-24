#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *bigint = parseBigInt("-2");
	BigInt *int2 = parseBigInt("2234");
	BigInt *int3 = parseBigInt("4469");
	printBigInt(sumBigInts(productBigInts(bigint,int2),int3));
	return 0;
}

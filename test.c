#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *int2 = parseBigInt("0");
	BigInt *int3 = parseBigInt("-1");
	printf("%d\n", greaterThanBigInt(int2,int3));
	return 0; 
}

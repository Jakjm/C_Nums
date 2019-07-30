#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
BigInt *power(BigInt *,BigInt *);
int main(int argc, char **argv){
	printBigInt(powerBigInts(parseBigInt("69"),parseBigInt("69")));
	return 0; 
}

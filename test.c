#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *b = parseBigInt("5");
	BigInt *e = parseBigInt("23");
	printBigInt(powerBigInts(b,e));
	return 0;
}

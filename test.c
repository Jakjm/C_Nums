#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *big = parseBigInt("2");
	BigInt *product = parseBigInt("1");
	BigInt *tmp;
	for(int i = 0;i < 500;++i){
		tmp = product;
		product = productBigInts(big,product);
		freeBigInt(tmp);
	}
	printBigInt(product);
	return 0;
}

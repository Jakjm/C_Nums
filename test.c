#include <stdio.h>
#include <stdlib.h>
#include "bigint.h"
int main(int argc, char **argv){
	BigInt *number = parseBigInt("-1000000");
	BigInt *number2 = parseBigInt("1000000");
	printBigInt(number);
	printBigInt(number2);
	printBigInt(sumBigInts(number,number2));
	return 0;
}

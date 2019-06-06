#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bigint.h"
int timeTest(){
	BigInt *currentNum;
	char *numStr;
	int index;
	long startClock, endClock, totalClocks;
	double time;
	numStr = malloc(sizeof(char) * 20);
	totalClocks = 0;
	for(index = -300000;index < 700000;++index){
		sprintf(numStr,"%d",index);
		startClock = clock();
		currentNum = parseBigInt(numStr);
		endClock = clock() - startClock;
		totalClocks += endClock;
	}
	time = (((double)totalClocks) / CLOCKS_PER_SEC) * 1000;
	printf("Total clocks %ld Nums:%d %.2fms\n",totalClocks,1000000,time);
	return 0;
}
int main(int argc, char **argv){
	BigInt *number = parseBigInt("-1002000");
	BigInt *number2 = parseBigInt("1000000");
	printBigInt(number);
	printBigInt(number2);
	printBigInt(difBigInts(number,number2));
	printBigInt(sumBigInts(number,number2));
	printBigInt(difBigInts(number2,number));
	timeTest();
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "bigint.h"

/**
 * Working on a bigint and bignumber personal project. 
 * @version June 23rd 2019
 * @author Jakjm - me
 */

//Bignum structure
typedef struct BigInt{
	short wholeSize; //The length of the unsigned char array.
	unsigned char *whole; //The address of the first unsigned char for the bignum. 
} BigInt;

//Frees the bigint structure. 
void freeBigInt(BigInt *b){
	free(b->whole);
	free(b);
}

//Verifies that a string is of a base 10 big integer format.
int checkBigInt(char *str){
	if(*str == '-' || *str == '+'){
		++str;
	}
	while(*str != '\0' && *str != '\n'){
		if(*str < '0' || *str > '9'){
			return 0;
		}
		++str;
	}
	return 1;
}
char *processNumber(char *);
void flipNegative(BigInt *);
void mulBigInt10(BigInt *);
BigInt *sumBigInts(BigInt *num1,BigInt *num2){
	BigInt *larger, *smaller, *newNum;
	int sum, carry, index, sign;
	if(num1->wholeSize > num2->wholeSize){
		larger = num1;
		smaller = num2;
	}
	else{
		larger = num2;
		smaller = num1;
	}
	sign = (smaller->whole[smaller->wholeSize - 1]) >> 7;
	newNum = malloc(sizeof(BigInt));
	newNum->wholeSize = larger->wholeSize;
	newNum->whole = malloc(sizeof(unsigned char) * (larger->wholeSize + 1));

	carry = 0;
	for(index = 0;index < smaller->wholeSize;++index){
		sum = larger->whole[index] + smaller->whole[index] + carry;
		carry = sum >> 8;
		newNum->whole[index] = sum - (carry << 8);
	}
	while(index < larger->wholeSize){
		sum = larger->whole[index] + carry + sign * 255;
		carry = sum >> 8;
		newNum->whole[index] = sum - (carry << 8);
		++index;
	}
	return newNum;
}
BigInt *difBigInts(BigInt *num1,BigInt *num2){
	BigInt *new;
	num2 = copyBigInt(num2);
	flipNegative(num2);
	new = sumBigInts(num1,num2);
	freeBigInt(num2);
	return new;
}
BigInt *allocBigInt(int);
BigInt *expBigInts(BigInt *num1,BigInt *num2){
	
}
BigInt *productBigInts(BigInt *num1,BigInt *num2){
	//Method variables. 
	unsigned char signOne, signTwo; 
	BigInt *new;
	unsigned int indexOne, indexTwo, product, carry, index;
	unsigned int *buf;
	
	signOne = num1->whole[num1->wholeSize - 1] >> 7;
	signTwo = num2->whole[num2->wholeSize - 1] >> 7;
	//If num1 is negative, make a positive copy in its place.
	if(signOne){
		num1 = copyBigInt(num1);
		flipNegative(num1);
	}
	//If num2 is negative, make a positive copy in its place.
	if(signTwo){
		num2 = copyBigInt(num2);
		flipNegative(num2);
	}

	new = allocBigInt(num1->wholeSize + num2->wholeSize);
	buf = calloc(new->wholeSize,sizeof(unsigned int));
	for(indexOne = 0;indexOne < num1->wholeSize;++indexOne){
		for(indexTwo = 0;indexTwo < num2->wholeSize;++indexTwo){
			product = num1->whole[indexOne] * num2->whole[indexTwo];
			buf[indexOne + indexTwo] += product; 
		}
	}
	carry = 0;
	for(index = 0;index < new->wholeSize;++index){
	 	buf[index] += carry;
		carry = buf[index] >> 8; 
		new->whole[index] = buf[index] - (carry << 8);
	}

	free(buf);

	//Free any copies of num1 or num2, if they were created.
	if(signOne){
		freeBigInt(num1);
	}
	if(signTwo){
		freeBigInt(num2);
	}

	//If only one of them was negative, the new number should be negative also. 
	if(signOne ^ signTwo){
		flipNegative(new);
	}
	return new;
}

//Parses a big integer from a given string. 
BigInt *parseBigInt(char *str){
	if(!checkBigInt(str)){
		return NULL;
	}
	else{
		int sum, currentBlock, sign, current, stringLength, numSize;
		int base = 256;
		double baseLog, numberSize;

		str = processNumber(str);
		//Determining sign from the string.
		if(*str == '-'){
			sign = 1;
			++str;
		}
		else if(*str == '+'){
			sign = 0;
			++str;
		}
		else{
			sign = 0;
		}

		//Skip to the next signifigant digit. 
		while(*str == '0' && *(str+1) != '\0'){
			++str;
		}

		//Calculating space needed for the bignum.
		stringLength = strlen(str);
		baseLog = log(base);
		numberSize = ceil((stringLength * log(10) + log(2)) / log(256));	
		numSize = (int)ceil(numberSize);

		//Updating the new bignum
		BigInt *newNum = malloc(sizeof(BigInt));
		newNum->wholeSize = numSize;
		newNum->whole = calloc(sizeof(unsigned char),numSize);
		
		//Loading digits into the bignum, converting the string into a 
		//Base 256 number. 
		while(*str != '\0'){
			mulBigInt10(newNum);
			current = *str - '0';

			sum = newNum->whole[0] + current;
			newNum->whole[0] = sum % base;
			currentBlock = 1;
			while(sum >= base && currentBlock < newNum->wholeSize){
				sum = newNum->whole[currentBlock] + 1;
				newNum->whole[currentBlock] = sum % base;
				++currentBlock;
			}
			++str;
		}
		if(sign){
			flipNegative(newNum);
		}
		return newNum;
	}
}
void printSpecs(BigInt *num){
	int index;
	printf("Digits %d\n",num->wholeSize);
	for(index = 0;index < num->wholeSize;++index){
		printf("Digit %d : %d\n",index,num->whole[index]);
	}
}
void flipNegative(BigInt *num){
	int index, sum, carry;
	for(index = 0;index < num->wholeSize;++index){
		num->whole[index] = ~num->whole[index];
	}
	index = 0;
	carry = 1;
	while(carry > 0 && index < num->wholeSize){
		sum = num->whole[index] + carry;
		num->whole[index] = sum % 256;
		carry = sum / 256; 
		++index;
	}
}
//Divides the bigint by 10. 
void divBigInt10(BigInt *num){
	int index, carry, sum; 
	carry = 0; 
	for(index = num->wholeSize - 1;index >= 0;--index){
		sum = carry * 256 + num->whole[index];
		carry = sum % 10;
		num->whole[index] = sum / 10;
	}
}
//Multiplies the big integer by 10
void mulBigInt10(BigInt *num){
	int index,carry,product;
	carry = 0; 
	for(index = 0;index < num->wholeSize;++index){
		product = num->whole[index] * 10 + carry;  
		num->whole[index] = product % 256; 
		carry = product / 256;
	}
}
/**
 * Copies the number after normalizing it. 
 */
char *processNumber(char *str){
	int currentIndex = 0;
	int strSize = strlen(str);
	char *newString = malloc(sizeof(char) * (strSize + 1));

	if(*str == '-'){
		*newString = '-';
		++str;
		++currentIndex; 
	}
	else if(*str == '+'){
	 	++str;
	}

	while(*str == '0' && *(str+1) != '\0'){
		++str;
	}

	//Copy the number until we're at the end of the string. 
	while(*str != '\0'){
		newString[currentIndex] = *str;
		++str;
		++currentIndex;
	}
	newString[currentIndex] = '\0';
	return newString; 
}
void reverseStr(char *);
int isZero(BigInt *num){
	int index;
	for(index = 0;index < num->wholeSize;++index){
		if(num->whole[index] != 0)return 0;
	}
	return 1;
}
//Creates a deep copy of a Bignum. 
BigInt *copyBigInt(BigInt *number){
	int index;
	BigInt *copy = malloc(sizeof(BigInt));
	copy->wholeSize = number->wholeSize;
	copy->whole = calloc(sizeof(unsigned char),copy->wholeSize);
	for(index = 0;index < copy->wholeSize;++index){
		copy->whole[index] = number->whole[index];
	}
	return copy;
}
//Allocates a bigint with the requested size...
BigInt *allocBigInt(int space){
	BigInt *new = malloc(sizeof(BigInt));
	new->wholeSize = space;
	new->whole = calloc(space,sizeof(unsigned char));
	return new;	
}
//Prints the biginteger as a hexadecimal string
void printBigIntHex(BigInt *num){
	int index;
	for(index = num->wholeSize - 1;index >= 0;--index){
		printf("%02x",num->whole[index]);
	}
	printf("\n");
}
/*
 *Generates a base 10 representation of the BigInt. 
 *@param BigInt * - the address of the big integer. 
 *@return str  - the base 10 representation of the BigInt, as a string. 
 */
char *bigIntToStr(BigInt *num){
	int index, sum, count, strIndex, strSize, sign;
	char *string;
	//Creating a copy of the num so we can destroy it to generate the base 10 string. 
	num = copyBigInt(num);

	//Calculating the length of string needed. 
	strSize = (int)ceil((num->wholeSize * log(256)) / log(10)) + 1;
	strIndex = 0;

	//Calculating the sign of the number
	sign = num->whole[num->wholeSize - 1] >> 7;
	if(sign){
		//Flip around the number, allocate another character for the negative sign. 
		flipNegative(num);
		string = malloc(sizeof(char) * (strSize + 1));
		*string = '-';
		++strIndex;
	}
	else{
		//Otherwise just use the space needed. 
		string = malloc(sizeof(char) * strSize);
	}
	for(count = 0;count < strSize;++count){
		sum = 0;
		for(index = num->wholeSize - 1;index > 0;--index){
			sum += num->whole[index] % 10;
		}
		sum *= 6;
		sum += num->whole[0];
		sum %= 10;
		divBigInt10(num);
		string[strIndex] = sum + '0';
		strIndex++;
		if(isZero(num))break;
	}
	string[strIndex] = '\0';
	reverseStr(string + sign);
	freeBigInt(num);
	return string;
}
//Prints a big int in decimal format.
void printBigInt(BigInt *num){
	char *str = bigIntToStr(num);
	printf("%s\n",str);
	free(str);
}
//Reverses a string
void reverseStr(char *str){
	int start = 0;
	int end = 0;
	int nul;
	char temp;
	while(str[end] != '\0'){
		++end;
	}
	nul = end;
	--end;
	while(start < nul && end > 0 && start < end){
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		++start;
		--end;
	}

}
int greaterThanBigInt(BigInt *num1,BigInt *num2){
	BigInt *cp1 = copyBigInt(num1);
	BigInt *cp2 = copyBigInt(num2);
	BigInt *dif = difBigInts(cp1,cp2);
	freeBigInt(cp1);
	freeBigInt(cp2);
	
	if(((dif->whole[dif->wholeSize-1]) >> 7) == 1){
		printf("Difference: ");
		printBigInt(dif);
		freeBigInt(dif);
		return 0;
	}
	else{
		for(int i = 0;i < dif->wholeSize;++i){
			if(dif->whole[i] != 0) {
				freeBigInt(dif);
				return 1;
			}	
		}
		freeBigInt(dif);
		return 0;
	}
}

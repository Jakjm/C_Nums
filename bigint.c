#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

/**
 * Working on a bigint and bignumber personal project. 
 * @version May 31st 2019
 * @author Jakjm - me
 */

//Bignum structure
typedef struct BigInt{
	short wholeSize; //The length of the unsigned char array.
	unsigned char *whole; //The address of the first unsigned char for the bignum. 
	char sign; //The sign of the bigint.
} BigInt;

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
void mulBigInt10(BigInt *);
//Parses a big integer from a given string. 
BigInt *parseBigInt(char *str){
	if(!checkBigInt(str)){
		return NULL;
	}
	else{
		BigInt *newNum = malloc(sizeof(BigInt));
		int sum, currentBlock;
		str = processNumber(str);

		//Determining sign from the string.
		if(*str == '-'){
			newNum->sign = 1;
			++str;
		}
		else if(*str == '+'){
			newNum->sign = 0;
			++str;
		}

		//Skip to the next signifigant digit. 
		while(*str == '0'){
			++str;
		}

		//Every byte-digit is worth 256
		int base = 256;

		//Calculating space needed for the bignum. 
		int stringLength = strlen(str);
		double baseLog = log(base);
		double mult = (stringLength - 1) * log(10)  / baseLog;
		double coFactor = log(*str - '0' + 1) / baseLog;
		int numSize = (int)ceil(mult + coFactor);
		
		
		unsigned short current = 0;

		//Updating the new bignum
		newNum->wholeSize = numSize;
		newNum->whole = malloc(sizeof(unsigned char) * numSize);
		
		//Loading digits into the bignum, converting the string into a 
		//Base 256 number. 
		while(*str != '\0'){
			mulBigInt10(newNum);
			current = *str - '0';


			sum = newNum->whole[0] + current;
			newNum->whole[0] = sum % 256;
			currentBlock = 1;
			while(sum > 256){
				sum = newNum->whole[currentBlock] + 1;
				newNum->whole[currentBlock] = sum % 256;
				++currentBlock;
			}
			++str;
		}

		return newNum;

	}
}

BigInt *difBigInts(BigInt *,BigInt *);
//Calculates the sum of two big integers.
BigInt *sumBigInts(BigInt *num1,BigInt *num2){
	if(num1->sign != num2 -> sign){
		BigInt *result, *minuend, *subtrahend;

		//Minuend becomes the non-negative number. 
		//Subtrahend becomes the negative one. 
		if(num1->sign == 1){
			minuend = num2;
			subtrahend = num1;
		}
		else{
			minuend = num1;
			subtrahend = num2;
		}
		subtrahend->sign == 0;
		result = difBigInts(minuend,subtrahend);
		subtrahend->sign == 1;
		return result;
	}
	
	int sum, carry, index;
	BigInt *smaller,*larger;
	if(num1->wholeSize > num2->wholeSize){
		larger = num1;
		smaller = num2;	
	}
	else{
		larger = num2;
		smaller = num1;
	}
	carry = 0;
	unsigned char *sumValue = malloc(sizeof(unsigned char) * (larger->wholeSize + 1));
	for(index = 0;index < smaller->wholeSize;++index){
		sum = larger->whole[index] + smaller->whole[index] + carry;
		sumValue[index] = sum % 256; 
		carry = sum / 256;
	}
	while(index < larger->wholeSize){
		sum = larger->whole[index] + carry;
		sumValue[index] = sum % 256;
		carry = sum / 256;
		++index;
	}
	if(carry == 1){
		sumValue[index] = 1;
	}
	BigInt *newInt = malloc(sizeof(BigInt));
	newInt->sign = larger->sign;
	newInt->whole = sumValue;
	newInt->wholeSize = larger->wholeSize + 1;
	return newInt;
}
//Calculates the difference of two big integers. 
BigInt *difBigInts(BigInt *num1,BigInt *num2){
	return NULL;
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
		product = num->whole[index] * 10; 
		num->whole[index] = product % 256 + carry; 
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
	while(*str == '0'){
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
	copy->sign = number->sign;
	copy->wholeSize = number->wholeSize;
	copy->whole = malloc(sizeof(unsigned char) * copy->wholeSize);
	for(index = 0;index < copy->wholeSize;++index){
		copy->whole[index] = number->whole[index];
	}
	return copy;
}
//Prints the biginteger as a hexadecimal string
void printBigIntHex(BigInt *num){
	int index;
	putchar(num->sign == 0 ? '\0' : '-');
	for(index = num->wholeSize;index >= 0;--index){
		printf("%x\n",num->whole[index]);
	}
}
//Prints a big int in decimal format.
void printBigInt(BigInt *num){
	int index, sum, count, strIndex, strSize;
	num = copyBigInt(num);
	strSize = (int)ceil((num->wholeSize * log(256)) / log(10));
	strIndex = 0;
	char *string = malloc(sizeof(char) * (strSize + 1));
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
	reverseStr(string);
	printf("%c%s\n",num->sign == 0 ? '\0' : '-',string);
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
//Test program for big integers.
int main(int argc, char **argv)
{
	char *numStr = "-456456";
	BigInt *number = parseBigInt(numStr);
	numStr = "-123123";
	BigInt *number2 = parseBigInt(numStr);
	printBigInt(number);
	printBigInt(number2);
	printBigInt(sumBigInts(number,number2));
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/**
 * Working on a bigint and bignumber personal project. 
 * @version May 21st 2019
 * @author Jakjm - me
 */


//Bignum structure
typedef struct Bignum{
	short wholeSize;
	unsigned char *whole;
	char sign;
} Bignum;

//Verifies that a string is of a numeric format.
int checkBignum(char *str){
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
void mulBignum10(Bignum *);
//Parses a bignum from a given string. 
Bignum *parseBignum(char *str){
	if(!checkBignum(str)){
		return NULL;
	}
	else{
		Bignum *newNum = malloc(sizeof(Bignum));
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
			mulBignum10(newNum);
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
void divBignum10(Bignum *num){
	int index, carry, sum; 
	carry = 0; 
	for(index = num->wholeSize - 1;index >= 0;--index){
		sum = carry * 256 + num->whole[index];
		carry = sum % 10;
		num->whole[index] = sum / 10;
	}
}
void mulBignum10(Bignum *num){
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
void printBignumHex(Bignum *num){
	int index;
	putchar(num->sign == 0 ? '\0' : '-');
	for(index = num->wholeSize;index >= 0;--index){
		printf("%x",num->whole[index]);
	}
}
void reverseStr(char *);
int isZero(Bignum *num){
	int index;
	for(index = 0;index < num->wholeSize;++index){
		if(num->whole[index] != 0)return 0;
	}
	return 1;
}
//Creates a deep copy of a Bignum. 
Bignum *copyBignum(Bignum *number){
	int index;
	Bignum *copy = malloc(sizeof(Bignum));
	copy->sign = number->sign;
	copy->wholeSize = number->wholeSize;
	copy->whole = malloc(sizeof(unsigned char) * copy->wholeSize);
	for(index = 0;index < copy->wholeSize;++index){
		copy->whole[index] = number->whole[index];
	}
	return copy;
}
//In development. 
void printBignum(Bignum *num){
	int index, sum, count, strIndex, strSize;
	//num = copyBignum(num);
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
		divBignum10(num);
		string[strIndex] = sum + '0';
		strIndex++;
		if(isZero(num))break;
	}
	string[strIndex] = '\0';
	reverseStr(string);
	printf("%c%s\n",num->sign == 0 ? '\0' : '-',string);
}
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
void checkString(char *str,int expectation){
	printf("Test: \"%s\" ~ %s Expected:%s\n",str,checkBignum(str) ? "Passed" : "Failed",expectation ? "Pass" : "Fail");
}
void testValidityTester(){
	checkString("111222333",1);
	checkString("-12-23-45",0);
	checkString("-000000002",1);
}
int main(int argc, char **argv)
{
	char *numStr = "-25923124124214214112312124";
	Bignum *number = parseBignum(numStr);
	printf("%s\n",numStr);
	printBignum(number);
	return 0;
}

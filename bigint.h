//Header file for the big Integer structure. 
typedef struct BigInt BigInt;

//Function for parsing a bigint from a string. 
BigInt *parseBigInt(char *);
void printBigInt(BigInt *);
char *bigIntToStr(BigInt *);
void printBigIntHex(BigInt *);
int checkBigInt(char *);
void printSpecs(BigInt *num);
void divBigInt2(BigInt *num);
void freeBigInt(BigInt *);
//Function for calculating the sum of two bigints.
BigInt *sumBigInts(BigInt *,BigInt *);
//Function for calculating the difference of two bigints. 
BigInt *difBigInts(BigInt *,BigInt *);
//Function for calculating the product of two bigints. 
BigInt *productBigInts(BigInt *,BigInt *);
//Function for calculating the value of the first bigint raised to the second. 
BigInt *powerBigInts(BigInt *,BigInt *);
//Function for calculating the quotient of two big integers...
BigInt *quotientBigInts(BigInt *,BigInt *);
BigInt *copyBigInt(BigInt *);

int lessThanBigInt(BigInt *,BigInt *);
/*Definitions for checking inequalities.*/
int greaterThanEqualBigInt(BigInt *,BigInt *);
int greaterThanBigInt(BigInt *,BigInt *);
int equalTo(BigInt *,BigInt*);

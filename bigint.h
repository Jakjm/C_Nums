//Header file for the big Integer structyure. 
typedef struct BigInt BigInt;

//Function for parsing a bigint from a string. 
BigInt *parseBigInt(char *);
void printBigInt(BigInt *);
char *bigIntToStr(BigInt *);
void printBigIntHex(BigInt *);
int checkBigInt(char *);
void printSpecs(BigInt *num);

//Function for calculating the sum of two bigints.
BigInt *sumBigInts(BigInt *,BigInt *);
//Function for calculating the difference of two bigints. 
BigInt *difBigInts(BigInt *,BigInt *);
//Function for calculating the product of two bigints. 
BigInt *productBigInts(BigInt *,BigInt *);

int lessThanBigInt(BigInt *,BigInt *);
int greaterThanBigInt(BigInt *,BigInt *);
int equalTo(BigInt *,BigInt*);

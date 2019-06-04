CC=gcc

run: bigint.c 
	$(CC) -o run bigint.c -lm

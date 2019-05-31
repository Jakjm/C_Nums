CC=gcc

run: bigints.c 
	$(CC) -o run bigints.c -lm

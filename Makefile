CC=gcc

run: bigint.c test.c
	$(CC) -o run test.c bigint.c -lm

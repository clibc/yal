CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c17 -pedantic

all:main.o
	$(CC) $(FLAGS) -o yal.out main.o lex.yy.c

main.o:main.c lex.yy.c
	$(CC) $(FLAGS) -c main.c 

lex.yy.c:test.l
	lex test.l

clean:
	rm -f *.o *.out *.core

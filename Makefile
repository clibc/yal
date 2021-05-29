CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c99 -pedantic

all:main.o lexer.o parser.o variable.o
	$(CC) $(FLAGS) -o a.out lexer.o parser.o variable.o main.o

main.o:./src/main.c
	$(CC) $(FLAGS) -c ./src/main.c 

parser.o:./src/parser.c
	$(CC) $(FLAGS) -c ./src/parser.c 

lexer.o:./src/lexer.c
	$(CC) $(FLAGS) -c ./src/lexer.c

variable.o:./src/variable.c
	$(CC) $(FLAGS) -c ./src/variable.c

clean:
	rm -f *.o *.out *.core

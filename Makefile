CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c99 -pedantic

OFILES=main.o lexer.o parser.o variable.o

all:$(OFILES)
	$(CC) $(FLAGS) -o a.out $(OFILES)

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

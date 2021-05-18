CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c17 -pedantic

all:main.o parser.o
	$(CC) $(FLAGS) -o a.out parser.o main.o

main.o:./src/main.c
	$(CC) $(FLAGS) -c ./src/main.c 

parser.o:./src/parser.c
	$(CC) $(FLAGS) -c ./src/parser.c 

clean:
	rm -f *.o *.out *.core

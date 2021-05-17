CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c17 -pedantic

all:main.o parser.o
	$(CC) $(FLAGS) -o a.out parser.o main.o

main.o:main.c
	$(CC) $(FLAGS) -c main.c 

parser.o:parser.c
	$(CC) $(FLAGS) -c parser.c 

clean:
	rm -f *.o *.out *.core

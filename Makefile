CC=gcc
FLAGS=-ggdb -Wall -Wextra -std=c17 -pedantic

all:main.o
	$(CC) $(FLAGS) -o a.out  main.o

main.o:main.c
	$(CC) $(FLAGS) -c main.c 

clean:
	rm -f *.o *.out *.core

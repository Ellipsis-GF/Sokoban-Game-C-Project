sokoban : main.o
	gcc -o sokoban main.o

main.o : main.c
	gcc -o main.o -c main.c

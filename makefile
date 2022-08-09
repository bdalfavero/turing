# makefile for turing simulator

turing: src/main.c src/main.o
	gcc src/main.o -o turing

main.o: src/main.c
	gcc -c src/main.c -o src/main.o
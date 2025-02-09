CC = gcc
CFLAGS = -Wall -std=c99 -g

all: infix_10 infix_32 infix_n

infix_10: infix.o number_10.o operation.o
	gcc infix.o number_10.o operation.o -o infix_10
    
infix_32: infix.o number_32.o operation.o
	gcc infix.o number_32.o operation.o -o infix_32
    
infix_n: infix.o number_n.o operation.o 
	gcc infix.o number_n.o operation.o -o infix_n
    
# Each Object File
infix.o: infix.c number.h operation.h
number_10.o: number_10.c number.h operation.h
number_32.o: number_32.c number.h operation.h
number_n.o: number_n.c number.h operation.h
operation.o: operation.c operation.h

clean:
	rm -f infix.o number_10.o number_32.o number_n.o operation.o
	rm -f infix_10 infix_32 infix_n
	rm -f output.txt
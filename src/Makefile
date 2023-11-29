CC=gcc
OPT=-Wall -Wextra
OPTPNG=-lpng

main: steg.o
	${CC} ${OPT} ${OPTPNG} steg.o -o main
steg.o: steg.c
	${CC} ${OPT} steg.c -c

clean:
	rm -f *.o *.gch


CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm

all: echoServer

echoServer: echoServer.o utils.o
	${CC} echoServer.o utils.o -o echoServer

utils.o: utils.c
	${CC} ${CFLAGS} utils.c

echoServer.o: echoServer.c
	${CC} ${CFLAGS} echoServer.c

clean:
	rm -f *.o *~

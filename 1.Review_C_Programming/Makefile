CFLAGS = -c -Wall
CC = gcc
LIBS =  -lm

all: schedule

schedule: schedule.o utils.o
	${CC} schedule.o utils.o -o schedule

utils.o: utils.c
	${CC} ${CFLAGS} utils.c

schedule.o: schedule.c
	${CC} ${CFLAGS} schedule.c

clean:
	rm -f *.o *~

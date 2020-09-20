#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCD_LENGTH 6

typedef struct subject{
    char code[7];
    char course[50];
    char day[10];
    char time[10];
    char period[10];
    char week[20];
    char room[10];
}Subject;

struct schedule{
    Subject subject;
    struct schedule *nextPtr;
};

typedef struct schedule Schedule;
typedef Schedule *SchedulePtr;

char *convert2Day(char num);
char *convert2Time(char num);
char *period(char *s1, char *s2);
char *week(char **tokens, int count);
char **tokenize(char *str, char *delimitador, int *count);
char *get_Room_period(SchedulePtr root, int period, char *day);
SchedulePtr makeNode(Subject v);
SchedulePtr append(SchedulePtr root, Subject sub);
int isEmpty(SchedulePtr root);
void printSchedule_1(SchedulePtr root);
void printSchedule_2(SchedulePtr root);
SchedulePtr readFile(FILE *fPtr);
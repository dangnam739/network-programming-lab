#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SCD_LENGTH 4

typedef struct Subject{
    char code[7];
    char course[50];
    char day[10];
    char time[10];
    char period[10];
    char week[10];
    char room;
}Subject;

struct schedule{
    Subject subject;
    struct schedule *nextPtr;
};

typedef struct schedule Schedule;
typedef Schedule *SchedulePtr;

void insert(SchedulePtr *root, Subject subject);
int isEmpty(SchedulePtr root);
void printSchedule(Schedule currentPtr);


void insert(SchedulePtr *root, Subject subject)
{
    SchedulePtr newPtr;
    SchedulePtr prevPtr;
    SchedulePtr curPtr;

    newPtr = malloc(sizeof(Schedule));

    if(newPtr != NULL){
        newPtr->subject = subject;
        newPtr->nextPtr = NULL;

        prevPtr = NULL;
        curPtr = *root;

        while(curPtr->nextPtr != NULL){
            curPtr = curPtr->nextPtr;
        }

        curPtr->nextPtr = newPtr;
    }
}


int isEmpty(SchedulePtr root){
    return root == NULL;
}

void printSchedule(Schedule currentPtr){

}

char *convert2Day(char num){
    if (num == '2')
        return "Monday";
    if (num == '3')
        return "Tuesday";
    if (num == '4')
        return "Wednesday";
    if (num == '5')
        return "Thursday";
    if (num == '6')
        return "Friday";
    if (num == '7')
        return "Saturday";
    if (num == '8')
        return "Sunday";
}

char *convert2Time(char num){
    if (num == '1')
        return "Morning";
    else
        return "Afternoon";

}

char** tokenize(char* str, char* delimitador)
{
    char* tmp;
    char** tokens;
    int i = 0;
    tokens = (char**)malloc(sizeof(char*) * SCD_LENGTH);

    tmp = strtok(str, delimitador);

    while (tmp != NULL)
    {
        tokens[i] = (char*)malloc((strlen(tmp) + 1) * sizeof(char));
        strcpy(tokens[i], tmp);
        tmp = strtok(NULL, delimitador);
        i++;
    }

    return tokens;
}

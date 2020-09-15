#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// void readFile(FILE *fPtr, SchedulePtr *root){
//     char *tmp;
//     char code[10];
//     char course[50];
//     char schedule[100];
//     Subject sub;


//     while (!feof(fPtr))
//     {
//         fscanf(fPtr, "%[^\n]\n", tmp);
//         char **tokens = tokenize(tmp, " ");

//         strcpy(sub.code, tokens[0]);
//         strcpy(sub.course, tokens[1]);

//         strcpy(sub.day, convert2Day(tokens[2][0]));
//         strcpy(sub.time, convert2Time(schedule[2][1]));
//     }
// }



int main(){
    FILE *fPtr;
    char *schedule;

    char** tokens;
    char *token;
    int i;
    char seps[] = " ";

    fPtr = fopen("schedule.txt", "r");

    while(!feof(fPtr)){
        fscanf(fPtr, "%[^\n]\n", schedule);
        token = strtok(schedule, seps);

        while(token != NULL){
            token = strtok(NULL, seps);
            printf("%s\n", token);
        }
    }


    fclose(fPtr);
    return 0;
}
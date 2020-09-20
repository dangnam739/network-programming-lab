#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main(){
    FILE *fPtr;
    fPtr = fopen("schedule.txt", "r");

    SchedulePtr root = NULL;
    root = readFile(fPtr);

    printSchedule_1(root);
    printSchedule_2(root);

    fclose(fPtr);
    return 0;
}
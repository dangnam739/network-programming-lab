#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

int main()
{
    FILE *fPtr;
    fPtr = fopen("schedule.txt", "r");

    SchedulePtr root = NULL;
    root = readFile(fPtr);
    char *buf;
    char *buffer;
    printf("Enter string: ");
    scanf("%s", buf);

    buffer = getSubject_by_day(root, buf);
    printf("%s\n", buffer);

    fclose(fPtr);
    return 0;
}
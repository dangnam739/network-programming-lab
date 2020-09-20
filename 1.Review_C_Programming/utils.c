#include "utils.h"


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

    return "";
}

char *convert2Time(char num){
    if (num == '1')
        return "Morning";
    else
        return "Afternoon";

}

char *period(char* s1, char* s2){
    char *ped;

    ped = (char *)malloc(4 * sizeof(char));

    strncpy(ped, &s1[2], 1);
    strcat(ped, "-");
    strncat(ped, &s2[2], 1);

    return ped;
}

char *week(char** tokens, int count){
    char *w;

    if(count != SCD_LENGTH){
        w = (char *)malloc((strlen(tokens[2]) + strlen(tokens[3]) + 1) * sizeof(char));
        strcpy(w, tokens[2]);
        strcat(w, ",");
        strcat(w, tokens[3]);
    }
    else
    {
        w = (char *)malloc((strlen(tokens[2]) + strlen(tokens[3]+strlen(tokens[4])) + 1) * sizeof(char));
        strcpy(w, tokens[2]);
        strcat(w, ",");
        strcat(w, tokens[3]);
        strcat(w, ",");
        strcat(w, tokens[4]);
    }

    return w;
}

char** tokenize(char* str, char* delimitador, int *count)
{
    char* tmp;
    char** tokens;
    int i = 0;
    (*count) = 0;
    tokens = (char **)malloc(sizeof(char *) * SCD_LENGTH);

    tmp = strtok(str, delimitador);

    while (tmp != NULL)
    {
        tokens[i] = (char *)malloc((strlen(tmp) + 1) * sizeof(char));
        strcpy(tokens[i], tmp);
        tmp = strtok(NULL, delimitador);
        i++;
        (*count)++;
    }
    return tokens;
}

char *get_Room_period(SchedulePtr root, int period, char *day)
{
    SchedulePtr cur = root;
    int start_period, end_period;

    while (cur != NULL)
    {
        if (strcmp(cur->subject.day, day) == 0)
        {
            if (strcmp(cur->subject.time, "Morning") == 0)
            {
                start_period = cur->subject.period[0] - 48;
                end_period = cur->subject.period[2] - 48;
            }
            else
            {
                start_period = cur->subject.period[0] - 48 + 6;
                end_period = cur->subject.period[2] - 48 + 6;
            }
            // printf("%d - %d\n", start_period, end_period);

            if (period >= start_period && period <= end_period)
                return cur->subject.room;
        }
        cur = cur->nextPtr;
    }

    return "";
}

SchedulePtr makeNode(Subject v)
{
    SchedulePtr new;
    new = malloc(sizeof(Schedule));

    new->subject = v;
    new->nextPtr = NULL;

    return new;
}

SchedulePtr append(SchedulePtr root, Subject sub)
{
    SchedulePtr cur;
    SchedulePtr new = makeNode(sub);

    if (root == NULL)
        return new;

    cur = root;
    while (cur->nextPtr != NULL)
        cur = cur->nextPtr;

    cur->nextPtr = new;

    return root;
}

int isEmpty(SchedulePtr root)
{
    return root == NULL;
}

void printSchedule_1(SchedulePtr root)
{
    SchedulePtr cur = root;

    printf("|%-10s|%-20s|%-10s|%-10s|%-10s|%-20s|%-10s|\n", "Code", "Course", "Week Day", "AM/PM", "Period", "Week", "Room");

    while (cur != NULL)
    {
        printf("|%-10s|%-20s|%-10s|%-10s|%-10s|%-20s|%-10s|\n", cur->subject.code, cur->subject.course, cur->subject.day, cur->subject.time, cur->subject.period, cur->subject.week, cur->subject.room);

        cur = cur->nextPtr;
    }
}

void printSchedule_2(SchedulePtr root)
{
    int i;

    printf("-------------------------------------------------------------------\n");
    printf("|%-10s|%-10s|%-10s|%-10s|%-10s|%-10s|\n", "Period", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday");
    printf("-------------------------------------------------------------------\n");

    for (i = 0; i < 12; i++)
    {
        printf("|%-10d", i + 1);
        printf("|%-10s", get_Room_period(root, i + 1, "Monday"));
        printf("|%-10s", get_Room_period(root, i + 1, "Tuesday"));
        printf("|%-10s", get_Room_period(root, i + 1, "Wednesday"));
        printf("|%-10s", get_Room_period(root, i + 1, "Thursday"));
        printf("|%-10s|\n", get_Room_period(root, i + 1, "Friday"));
    }
    printf("-------------------------------------------------------------------\n");
}

SchedulePtr readFile(FILE *fPtr)
{
    char schedule[100];
    int count;
    char **tokens;
    Subject sub;
    SchedulePtr root = NULL;

    while (!feof(fPtr))
    {
        fscanf(fPtr, "%s%*c", sub.code);
        fscanf(fPtr, "%[^[0-9]]", sub.course);
        fscanf(fPtr, "%[^\n]\n", schedule);

        strcpy(sub.day, convert2Day(schedule[0]));
        strcpy(sub.time, convert2Time(schedule[1]));

        tokens = tokenize(schedule, ",", &count);

        strcpy(sub.period, period(tokens[0], tokens[1]));
        strcpy(sub.week, week(tokens, count));

        if (count == SCD_LENGTH)
            strcpy(sub.room, tokens[SCD_LENGTH - 1]);
        else
            strcpy(sub.room, tokens[SCD_LENGTH - 2]);

        // printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n", sub.code, sub.course, sub.time, sub.day, sub.period, sub.week, sub.room);
        root = append(root, sub);
    }

    return root;
}
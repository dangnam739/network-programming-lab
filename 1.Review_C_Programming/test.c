#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(void){
    char string[] = "IT3080 Computer Network    523,526,22,25-31,33-40,TC-502";
    char seps[] = " ";
    char *token;

    token = strtok(string, seps);
    while(token != NULL){
        printf("%s\n", token);
        token = strtok(NULL, seps);
    }
}
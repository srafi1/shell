#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int count_char(char c, char* string) {
    int counter = 0;
    //printf("counting '%c' in '%s'\n", c, string);
    while (*string) {
        //printf("%c", *string);
        if (c == *string) {
            counter++;
        }
        string++;
    }
    return counter;
}

void printarr(char** args) {
    int i;
    printf("[");
    while (args[i]) {
        printf("%s, ", args[i]);
        i++;
    }
    printf("]\n");
}

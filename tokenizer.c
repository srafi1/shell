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

void shift_array_back_at(char** original, int length) {
    for (int i = 0; i < length; i++) {
        original[i] = original[i + 1];
    }
}

void shift_string_back_at(char* original) {
    for (int i = 0; i < strlen(original) + 1; i++) {
        original[i] = original[i + 1];
    }
}

void strip_extra_blankspace(char* original) {
    char* loc = strstr(original, "\t");
    while (loc) {
        shift_string_back_at(loc);
        loc = strstr(original, "\t");
    }
    loc = strstr(original, "\n");
    while (loc) {
        shift_string_back_at(loc);
        loc = strstr(original, "\n");
    }
    loc = strstr(original, "  ");
    while (loc) {
        shift_string_back_at(loc);
        loc = strstr(original, "  ");
    }
    loc = strstr(original, " ;");
    while (loc) {
        shift_string_back_at(loc);
        loc = strstr(original, " ;");
    }
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

char ** parse_args(char* line) {
    int len = count_char(' ', line) + 2;
    char ** args = (char **) calloc(len, sizeof(char*));
    int index = 0;
    while (line) {
        args[index] = strsep(&line, " ");
        index += 1;
    }
    // calloc makes sure the last thing will already be NULL
    //printf("len: %d", len);
    //printarr(args);
    while (len > 2 && !args[0][0]) {
        shift_array_back_at(args, len);
        len--;
    }
    return args;
}


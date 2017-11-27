#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tokenizer.h"

char ** parse_args(char* line) {
    char ** args = (char **) calloc(count_char(' ', line) + 2, sizeof(char*));
    int index = 0;
    while (line) {
        args[index] = strsep(&line, " ");
        index += 1;
    }
    // calloc makes sure the last thing will already be NULL
    return args;
}

void exec_in_fork(char* command) {
    int f = fork();
    if (f) {
        wait();
    } else {
        char** args = parse_args(command);
        execvp(args[0], args);
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
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
    char** args = parse_args(command);
    if (strcmp("exit", args[0]) == 0) {
        exit(0);
    }
    int f = fork();
    if (f) {
        int status;
        wait(&status);
    } else {
        execvp(args[0], args);
        exit(0);
    }
}

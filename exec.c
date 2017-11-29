#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "tokenizer.h"

void exec_in_fork(char* command) {
    char** args = parse_args(command);
    if (strcmp("exit", args[0]) == 0) {
        exit(0);
    }
    if (strcmp("cd", args[0]) == 0) {
        chdir(args[1]);
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

void exec_all_in_line(char* line) {
    while (line) {
        exec_in_fork(strsep(&line, ";"));
    }
}

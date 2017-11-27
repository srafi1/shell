#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tokenizer.h"
#include "exec.h"

int main() {
    char user[256];
    getlogin_r(user, sizeof(user));
    while (1) {
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        char* ending_cwd = strrchr(cwd, '/') + 1;
        printf("%s:%s$ ", user, ending_cwd);
        char input[256];
        fgets(input, 256, stdin);
        *strchr(input, '\n') = 0; //change \n to null in input
        //printf("input: %s\n", input);
        if (strncmp("exit ", input, 5) == 0) {
            exit(0);
        }
        exec_in_fork(input);
    }

    return 0;
}

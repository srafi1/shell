#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tokenizer.h"
#include "exec.h"

int main() {
    while (1) {
        char cwd[256];
        getcwd(cwd, sizeof(cwd));
        printf("%s$ ", cwd);
        char input[256];
        fgets(input, 256, stdin);
        *strchr(input, '\n') = 0; //change \n to null in input
        //printf("input: %s\n", input);
        exec_all_in_line(input);
    }

    return 0;
}

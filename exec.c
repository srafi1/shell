#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "tokenizer.h"

/* void exec_in_fork
forks and then runs given command in the child process

args:
    command: command to be run
    in: filename to look for stdin or NULL
    out: filename to look for stdout or NULL
return:

*/
void exec_in_fork(char* command, char* in, char* out) {
    char** args = parse_args(command);
    if (strcmp("exit", args[0]) == 0) {
        exit(0);
    }
    if (strcmp("cd", args[0]) == 0) {
        chdir(args[1]);
        return;
    }
    int f = fork();
    if (f) {
        int status;
        wait(&status);
        free(args);
    } else {
        if (in) {
            //printf("setting stdin to: %s\n", in);
            int fd_in = open(in, O_RDONLY, NULL);
            dup2(fd_in, STDIN_FILENO);
        }
        if (out) {
            //printf("setting stdout to: %s\n", out);
            int fd_out = open(out, O_CREAT | O_WRONLY, 0660);
            dup2(fd_out, STDOUT_FILENO);
        }
        execvp(args[0], args);
        if (args[0][0]) {
            printf("'%s' is not a valid command\n", args[0]);
        }
        exit(0);
    }
}

/* void exec_pipe
forks and then runs given commands, piping input from one to the other

args:
    cmd1: command to take input from
    cmd2: command to give input to
return:

*/
void exec_pipe(char* cmd1, char* cmd2) {
    //printf("cmd1: %s\n", cmd1);
    //printf("cmd2: %s\n", cmd2);
    if (!cmd1[0] || !cmd2[0]) {
        return;
    }
    char** args = parse_args(cmd2);
    if (strcmp("exit", args[0]) == 0) {
        exit(0);
    }
    int f = fork();
    if (f) {
        int status;
        wait(&status);
        free(args);
    } else {
        FILE* pipe = popen(cmd1, "r");
        int pipe_fd = fileno(pipe);
        dup2(pipe_fd, STDIN_FILENO);
        execvp(args[0], args);
        pclose(pipe);
        if (args[0][0]) {
            printf("'%s' is not a valid command\n", args[0]);
        }
        exit(0);
    }
    //printf("done with pipe\n");
}

/* void exec_all_in_line
splits line by semicolons and executes each portion separately

args:
    line: line of commands
return:

*/
void exec_all_in_line(char* line) {
    while (line) {
        char* pipe_loc = strchr(line, '|');
        if (pipe_loc) {
            char* cmd1 = line;
            char* cmd2 = pipe_loc + 1;
            *pipe_loc = 0;
            strip_extra_blankspace(cmd1);
            strip_extra_blankspace(cmd2);
            exec_pipe(cmd1, cmd2);
            strsep(&line, ";");
        } else {
            char* in = get_stdin(line);
            char* out = get_stdout(line);
            delete_stdout(line);
            delete_stdin(line);
            //printf("final command: %s\n", line);
            exec_in_fork(strsep(&line, ";"), in, out);
            free(in);
            free(out);
        }
    }
}

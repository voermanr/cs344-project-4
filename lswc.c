#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int tokenize_string(char *buf, char **argv);

int build_argv(int *argc, char *buf, char **argv);

int main(int argc, char *argv[]) {
    int tube[2];
    pipe(tube);

    if (argc == 1) {

    }

    pid_t pid = fork();
    char *fnc[2];
    if (pid == 0) {
        dup2(STDIN_FILENO, tube[0]);
        close(tube[1]);
        fnc[0] = "wc";
        fnc[1] = "-l";
        execlp(fnc[0],fnc[1]);
    } else {
        dup2(tube[1], STDOUT_FILENO);
        close(tube[0]);
        fnc[0] = "ls";
        fnc[1] = "-1a";
        execlp(fnc[0], fnc[1]);
    }
}
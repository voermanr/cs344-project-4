#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "string.h"

int execute_child(const int *tube, char **fnc);
int execute_parent(const int *tube, char **fnc, const int *argc, char *argv[]);

int main(int argc, char *argv[]) {

    if (argc > 2) {
        perror("too many arguments.");
    }

    int tube[2];
    if (pipe(tube) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    char *fnc[3];

    pid == 0 ? execute_child(tube, fnc) : execute_parent(tube, fnc, &argc, argv);
}

int execute_parent(const int *tube, char **fnc, const int *argc, char *argv[]) {
    close(tube[0]);
    dup2(tube[1], STDOUT_FILENO);
    close(tube[1]);

    fnc[0] = "ls";
    fnc[1] = "-1a";
    char *dir = ".";

    if (*argc == 2) {
        dir = argv[1];
    }

    execlp(fnc[0], fnc[0], fnc[1], dir, NULL);

    return 0;
}

int execute_child(const int *tube, char **fnc) {
    close(tube[1]);
    dup2(tube[0], STDIN_FILENO);
    close(tube[0]);

    fnc[0] = "wc";
    fnc[1] = "-l";

    execlp(fnc[0],fnc[0], fnc[1], NULL);

    return 0;
}


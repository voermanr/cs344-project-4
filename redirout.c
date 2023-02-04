#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"

#define BUFF_SIZE 1024

int main (int argc, char *argv[]){
    if (argc < 2) {
        fprintf(stderr,"too few arguments.");
        return EXIT_FAILURE;
    }

    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644);

    int tube[2];
    if (pipe(tube) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        close(tube[0]);
        dup2(tube[1], STDOUT_FILENO);
        close(tube[1]);
        execvp(argv[2], argv + 2);
        perror("execvp");
        return EXIT_FAILURE;
    }

    else {
        char buf[BUFF_SIZE];
        close(tube[1]);

        ssize_t bytes_read, bytes_wrote;

        while ((bytes_read = read(tube[0],buf, sizeof(buf))) > 0) {
            bytes_wrote = write(fd, buf,bytes_read);
        }
        if (bytes_read == -1) {
            perror("read");
        }
        if (bytes_wrote == -1) {
            perror("write");
        }
    }
    return 0;
}
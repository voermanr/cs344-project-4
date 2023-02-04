#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"

int main (int argc, char **argv){
    //TODO: Check command line

    int fd = open(argv[1], O_CREAT | O_WRONLY, 644);

    return 0;
}
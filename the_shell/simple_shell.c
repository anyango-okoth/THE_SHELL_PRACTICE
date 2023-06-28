#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[], char *envp[]) {
    if (argc == 1) {
        prompt(envp);
    } else {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}


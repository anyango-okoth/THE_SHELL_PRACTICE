#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

void executeCommand(char *args[], char *envp[]) {
    if (args[0] != NULL) {
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL || strcmp(args[1], "~") == 0) {
                args[1] = getenv("HOME");
            } else if (strcmp(args[1], "-") == 0) {
                args[1] = getenv("OLDPWD");
            }

            if (chdir(args[1]) == 0) {
                char currentDir[1024];
                getcwd(currentDir, sizeof(currentDir));
                setenv("PWD", currentDir, 1);
                setenv("OLDPWD", getenv("PWD"), 1);
            } else {
                fprintf(stderr, "Failed to change directory\n");
            }
        } else {
            pid_t pid = fork();
            if (pid < 0) {
                fprintf(stderr, "Fork failed\n");
                exit(EXIT_FAILURE);
            } else if (pid == 0) {
                execvp(args[0], args);
                fprintf(stderr, "Failed to execute command\n");
                exit(EXIT_FAILURE);
            } else {
                wait(NULL);
            }
        }
    }
    (void)envp; /* Avoid "unused parameter" warning */
}


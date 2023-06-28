#include <stdlib.h>
#include <string.h>
#include "main.h"

void tokenizeString(char *string, char *args[], size_t maxArgs) {
    size_t argCount = 0;
    size_t stringLen = strlen(string);
    size_t start = 0;
    size_t end = 0;
    size_t wordLen;

    while (start < stringLen && argCount < maxArgs) {
        /* Find the start and end indices of the next word */
        while (start < stringLen && string[start] == ' ') {
            start++;
        }
        end = start;
        while (end < stringLen && string[end] != ' ') {
            end++;
        }

        /* Extract the word and copy it into the arguments array */
        wordLen = end - start;
        args[argCount] = (char*) malloc(wordLen + 1);
        strncpy(args[argCount], string + start, wordLen);
        args[argCount][wordLen] = '\0';

        argCount++;
        start = end;
    }

    args[argCount] = NULL;  /* Add NULL terminator */
}


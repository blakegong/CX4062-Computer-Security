#include <stdio.h>
#include <string.h>

#define CACHE_MAX 1024

int main(int argc, char *argv[]) {
    FILE *fp;
    char command[CACHE_MAX], result[CACHE_MAX];

    // strcpy(command, "ls -l ~");
    strcpy(command, "/home/alice/Public/mysecret \"&& ls -l /home/alice/Private\"");

    fp = popen(command, "r");
    if (fp == NULL)
        printf("ERROR");

    int count = 0;
    while (fgets(result, CACHE_MAX, fp) != NULL) {
        int i = 0;
        while (i < CACHE_MAX && result[i] != '\0') {
            if (count == 2)
                printf("%c", result[i]);
            else if (result[i] == '\n')
                count++;
            i++;
        }
    }

    pclose(fp);

    return 0;
}

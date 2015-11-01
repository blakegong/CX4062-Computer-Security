#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_MAX 1024


int test_password(char password[]) {
    char command[CACHE_MAX], result[CACHE_MAX], read_cache[CACHE_MAX];
    strcpy(result, "");
    snprintf(command, sizeof(command), "/home/alice/Public/admin-secret %s", password);
    FILE *fp;
    fp = popen(command, "r");
    if (fp == NULL)
        printf("ERROR!!\n");
    while (fgets(read_cache, CACHE_MAX, fp) != NULL) {
        strcat(result, read_cache);
    }
    printf("%s\n", result);
    pclose(fp);
    if (result[0] == 'S')
        return 1;
    else if (strlen(result) <= 33)
        return -1;
    else
        return 0;
}

int main(int argc, char *argv[])
{
    int n, test_result;
    char c, password[CACHE_MAX], password_16[CACHE_MAX];

    strcpy(password_16, "1234567890123456");

    for (n = 0; n < 14; n++) {
        for (c = 'a'; c <= 'z'; c++) {
            password_16[n] = c;
            if (test_password(password_16) == 0) {
                password_16[n] = c - 1;
                break;
            }
        }
        strncpy(password, password_16, n);
        if (test_password(password) == 1) {
            printf("Password:  %s\n", password);
        }
    }

    return 0;
}

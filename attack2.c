#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_MAX 1024

void execute_as_alice(char command[]) {
    char command_alice[CACHE_MAX], result[CACHE_MAX];
    snprintf(command_alice, sizeof(command_alice), "/home/alice/Public/mysecret \"&& %s \"", command);

    FILE *fp;
    fp = popen(command_alice, "r");
    if (fp == NULL)
        printf("ERROR!!\n");
    while (fgets(result, CACHE_MAX, fp) != NULL) {
        continue;
    }
    pclose(fp);
}

void sanitize(char user[], char *arg) {
    int i, pos = 0;
    for (i = 0; i < 15 && arg != NULL && *arg != '\0'; i++) {
        if (*arg >= 'a' && *arg <= 'z') {
            user[pos++] = *arg;
        }
        arg++;
    }
    user[pos] = '\0';
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char user[15];
	char command[CACHE_MAX], result[CACHE_MAX];

    if (argc < 2) {
        printf("Please input username! \n");
        return 1;
    }

    sanitize(user, argv[1]);

    snprintf(command, sizeof(command), "mv -f /home/alice/Private/password-%s /home/alice/Private/password-temp;", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "echo -n \'password\' > /home/alice/Private/password-%s", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "/home/alice/Public/user-secret %s password;", user);
    system(command);

    snprintf(command, sizeof(command), "rm -f /home/alice/Private/password-%s;", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "mv -f /home/alice/Private/password-temp /home/alice/Private/password-%s;", user);
    execute_as_alice(command);

    return 0;
}

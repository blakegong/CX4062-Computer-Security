#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char command[512], result[1024];

	strcpy(command, "/home/alice/Public/mysecret \"&& ls -l /home/alice/Private\"");

	fp = popen(command, "r");
	if (fp == NULL)
		printf("ERROR");

	while (fgets(result, 1024, fp) != NULL)
	    printf("%s", result);

	status = pclose(fp);
	if (status == -1) {
	    /* Error reported by pclose() */
	} else {
	    /* Use macros described under wait() to inspect `status' in order
	       to determine success/failure of command executed by popen() */
	}

	return 0;
}

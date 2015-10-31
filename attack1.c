#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	char command[512];
	
	fp = popen(command, "r");
	if (fp == NULL)
		printf("ERROR");
	
	while (
   strcpy(command, "/bin/bash -p -c \"echo $USER; /home/alice/Public/mysecret.sh ");
   strcat(command, argv[1]);
   strcat(command, "\"");
   system(command);


   return 0;
}

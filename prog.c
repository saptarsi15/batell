#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int parse(char *line, char **argv)
{
    if(*line != '\0')
    {
		while (*line != '\0')
		{
			while (*line == ' ' || *line == '\t' || *line == '\n')
				*line++ = '\0';
			*argv++ = line;
			while (*line != '\0' && *line != ' ' && *line != '\t' && *line != '\n') 
				line++;
		}
		*argv = '\0';
		*argv--;
		return 1;
	}
    else
    {
    	return 0;
	}
}

void execute(char **argv)
{
    int pid;
    int status;
    if ((pid = fork()) < 0)
    {
        printf("*** ERROR: forking child process failed\n");
        exit(1);
    }
    else if (pid == 0)
    {
        if (execvp(*argv, argv) < 0)
        {
             printf("*** ERROR: exec failed\n");
             exit(1);
        }
    }
    else
    {
        while (wait(&status) != pid);
    }
}

void main(void)
{
	char line[1024];
	char *argv[64];
	char c;
	int e=0,i;
	printf("\nWelcome to Batell, your very own fun-to-use shell\nPlease enter your commands at the prompt...\n");
	while (1)
	{
		printf("(>Y<) ");
		i=0;
		fflush(stdin);
		while((c=fgetc(stdin))!='\n')
		{
			line[i]=c;
			i++;
			if(i>1022)
			{
				printf("\nText limit reached!, please shorten your command...");
				break;
			}
		}
		line[i]='\0';
		e = parse(line, argv);
		if(e != 0)
		{
			if(strcmp(argv[0], "exit") == 0)
				exit(0);
			execute(argv);
		}
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10

/**
 * main - main function
 *
 *
 * Return: 0
 */

int main(void)
{

	char *input;
	char **environ;
	size_t bufsize = 32;
	int characters;

	input = (char *)malloc(bufsize * sizeof(char));

	if (input == NULL)
	{
		perror("malloc failed");
		exit(EXIT_FAILURE);
	}
	    while (1)
	    {
		printf("$ ");
		characters = getline(&input, &bufsize, stdin);

		if (characters == EOF)
		{
			printf("\n");
			break;
		}

		input[characters - 1] = '\0';

		char *args[MAX_ARGS];
		char *token = strtok(input, " ");
		int i = 0;
		while (token != NULL && i < MAX_ARGS - 1)
		{
			args[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		args[i] = NULL;

		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		else if (strcmp(args[0], "env") == 0)
		{
			char **env = environ;
			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
			continue;
		}

		if (fork() == 0)
		{
			execvp(args[0], args);
			printf("%s: command not found\n", args[0]);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
		}
	    }

	    free(input);
	    return (0);
}

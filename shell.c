#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 100

void parse_line(char *line, char *argv[])
{
    char *token;
    int argc = 0;

    token = strtok(line, " ");
    while (token != NULL && argc < MAX_ARGS - 1)
    {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    argv[argc] = NULL;
}

int main(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *argv[MAX_ARGS];
    int status;
    pid_t pid;

    while (1)
    {
        printf("$ ");
        nread = getline(&line, &len, stdin);
        if (nread == -1)
        {
            if (feof(stdin))
            {
		    printf("\n");
                break;
            }
            perror("getline");
            exit(EXIT_FAILURE);
        }

        /* Remove trailing newline character */
        if (line[nread - 1] == '\n')
            line[nread - 1] = '\0';

        /* Split the line into arguments */
        parse_line(line, argv);

        /* Exit the shell if the user inputs "exit" */
        if (strcmp(argv[0], "exit") == 0)
            break;

        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pid == 0)
        {
            /* Child process */
            if (execvp(argv[0], argv) == -1)
            {
                perror(argv[0]);
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            /* Parent process */
            waitpid(pid, &status, 0);

            /**Print the prompt if the child process exited normally*/
       }
    }

    free(line);
    exit(EXIT_SUCCESS);
}

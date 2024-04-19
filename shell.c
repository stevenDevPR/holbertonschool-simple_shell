#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

/* Function prototypes */
void print_env();

int main(void)
{
    char input[MAX_INPUT_LENGTH]; /* Buffer to store user input */
    int status; /* Status of child process */
    pid_t pid;

    while (1)
    {
        /* Display prompt */
        printf("($) ");

        /* Read user input */
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            if (feof(stdin))
            {
                printf("\n"); /* Print newline for EOF */
                break; /* Exit loop on EOF */
            }
            else
            {
                perror("fgets"); /* Print error message for other errors */
                exit(EXIT_FAILURE);
            }
        }

        /* Remove newline character from the end of input */
        input[strcspn(input, "\n")] = '\0';

        /* Check if the command is "exit" */
        if (strcmp(input, "exit") == 0)
        {
            break; /* Exit loop and shell */
        }

        /* Check if the command is "env" */
        if (strcmp(input, "env") == 0)
        {
            /* Print current environment variables */
            print_env();
            continue; /* Skip executing command */
        }

        /* Fork a new process */
        pid = fork();
        if (pid == -1)
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0)
        {
            /* Child process */
            execl(input, input, (char *)NULL);
            /* If execl returns, it means command execution failed */
            perror(input);
            exit(EXIT_FAILURE);
        }
        else
        {
            /* Parent process */
            /* Wait for child process to finish */
            if (wait(&status) == -1)
            {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    return EXIT_SUCCESS;
}

/* Function to print environment variables */
void print_env()
{
    extern char **environ; /* External variable for accessing environment variables */
    char **env;
    for (env = environ; *env != NULL; env++)
    {
        printf("%s\n", *env);
    }
}

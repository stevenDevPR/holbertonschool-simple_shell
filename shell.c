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
    char command_path[MAX_INPUT_LENGTH];
    pid_t pid;

    FILE *input_file;

    /* Open a temporary file for writing */
    input_file = fopen("input.txt", "w");
    if (input_file == NULL)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        /* Display prompt */
        printf("($) ");

        /* Read user input */
        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL)
        {
            printf("\n"); /* Print newline for EOF */
            break; /* Exit loop on EOF */
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

        /* Use the input as the command path */
        strncpy(command_path, input, MAX_INPUT_LENGTH);

        /* Write input to the temporary file */
        fprintf(input_file, "%s\n", input);

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
            /* Close the file descriptor for the input file */
            fclose(input_file);

            /* Open the temporary file for reading */
            input_file = fopen("input.txt", "r");
            if (input_file == NULL)
            {
                perror("fopen");
                exit(EXIT_FAILURE);
            }

            /* Redirect stdin to the temporary file */
            if (dup2(fileno(input_file), STDIN_FILENO) == -1)
            {
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            /* Execute the command */
            execl(command_path, input, (char *)NULL);
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

            /* Rewind the input file */
            rewind(input_file);
        }
    }

    /* Close the input file */
    fclose(input_file);

    /* Remove the temporary file */
    remove("input.txt");

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

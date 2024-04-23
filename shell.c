#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main(void)
{
<<<<<<< HEAD
    char input[MAX_INPUT_LENGTH]; /* Buffer to store user input */
    int status; /* Status of child process */
    char command_path[MAX_INPUT_LENGTH];
=======
    char cwd[MAX_COMMAND_LENGTH];
    char *path;
    size_t path_len;
    size_t new_path_len;
    char *new_path;
>>>>>>> steven_branch
    pid_t pid;
    char cmd_with_path[MAX_COMMAND_LENGTH];

    /* Get the current directory */
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        perror("getcwd");
        return EXIT_FAILURE;
    }

    /* Get the length of the PATH environment variable */
    path = getenv("PATH");
    path_len = strlen(path);

    /* Calculate the total length of new_path */
    new_path_len = strlen("PATH=") + strlen(cwd) + 1 + path_len + 1;

    /* Allocate memory for new_path */
    new_path = (char *)malloc(new_path_len);
    if (new_path == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    /* Construct the new PATH variable */
    snprintf(new_path, new_path_len, "PATH=%s:%s", cwd, path);

    /* Set the new PATH variable in the environment */
    if (putenv(new_path) != 0) {
        perror("putenv");
        free(new_path);
        return EXIT_FAILURE;
    }

    /* Main shell loop */
    while (1) {
        char command[MAX_COMMAND_LENGTH];
        char *cmd_argv[MAX_ARGS];
        int i;

<<<<<<< HEAD
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
=======
        /* Display prompt */
        printf("($) ");

        /* Read command from stdin */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n"); /* Print newline and exit on EOF (Ctrl+D) */
            break;
>>>>>>> steven_branch
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

	 if (strcmp(command, "exit") == 0) {
            break; /* Exit the shell */
        }

        /* Tokenize command */
        cmd_argv[0] = strtok(command, " ");
        for (i = 1; i < MAX_ARGS; i++) {
            cmd_argv[i] = strtok(NULL, " ");
            if (cmd_argv[i] == NULL) break;
        }
        cmd_argv[MAX_ARGS - 1] = NULL; /* Ensure the last element is NULL */

        /* Use the input as the command path */
        strncpy(command_path, input, MAX_INPUT_LENGTH);

        /* Write input to the temporary file */
        fprintf(input_file, "%s\n", input);

        /* Fork a new process */
        pid = fork();
        if (pid == -1) {
            perror("fork");
            free(new_path);
            return EXIT_FAILURE;
        }

        if (pid == 0) {
            /* Child process */
<<<<<<< HEAD
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
=======
            /* Execute the command */
            execvp(cmd_argv[0], cmd_argv);

            /* If execvp returns, it means command execution failed */
            /* Try executing the command with the full path */
            snprintf(cmd_with_path, sizeof(cmd_with_path), "/bin/%s", cmd_argv[0]);
            execvp(cmd_with_path, cmd_argv);

            /* If execvp returns, it means command execution failed */
            perror(cmd_argv[0]);
            free(new_path);
            return EXIT_FAILURE;
        } else {
>>>>>>> steven_branch
            /* Parent process */
            /* Wait for child process to finish */
            int status;
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                free(new_path);
                return EXIT_FAILURE;
            }

            /* Rewind the input file */
            rewind(input_file);
        }
    }

<<<<<<< HEAD
    /* Close the input file */
    fclose(input_file);

    /* Remove the temporary file */
    remove("input.txt");

=======
    free(new_path);
>>>>>>> steven_branch
    return EXIT_SUCCESS;
}

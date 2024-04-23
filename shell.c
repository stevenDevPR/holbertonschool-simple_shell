#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGS 64

int main(void) {
    char cwd[MAX_COMMAND_LENGTH];
    char *path;
    size_t path_len;
    size_t new_path_len;
    char *new_path;

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
        pid_t pid;
        int status;

        /* Print shell prompt */
        printf("($) ");

        /* Read command from stdin */
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n"); /* Print newline and exit on EOF (Ctrl+D) */
            break;
        }

        /* Remove newline character */
        command[strcspn(command, "\n")] = '\0';

        /* Check if the command is "exit" */
        if (strcmp(command, "exit") == 0) {
            break; /* Exit the shell */
        }

        /* Fork a new process */
        pid = fork();
        if (pid == -1) {
            perror("fork");
            free(new_path);
            return EXIT_FAILURE;
        }

        if (pid == 0) {
            /* Child process */
            /* Execute the command */
            execlp(command, command, NULL);

            /* If execlp returns, it means command execution failed */
            perror(command);
            free(new_path);
            return EXIT_FAILURE;
        } else {
            /* Parent process */
            /* Wait for child process to finish */
            if (waitpid(pid, &status, 0) == -1) {
                perror("waitpid");
                free(new_path);
                return EXIT_FAILURE;
            }
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                /* Command executed successfully */
                printf("\n"); /* Print newline after successful command execution */
            }
        }
    }

    free(new_path);
    return EXIT_SUCCESS;
}

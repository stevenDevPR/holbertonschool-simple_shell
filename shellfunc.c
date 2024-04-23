#include "main.h"

/**
 * display_shell_prompt - displays the shell prompt.
*/
void display_shell_prompt(void)
{
    printf(">>>> ");
    fflush(stdout);
}

/**
 * remove_newline_character - removes the newline character from a string.
 * @str: The string to modify.
*/
void remove_newline_character(char *str)
{
    char *newline = strchr(str, '\n');

    if (newline != NULL)
    {
        *newline = '\0';
    }
}

/**
 * execute_shell_command - executes the provided shell command.
 * @command: The command to execute.
 *
 * Return: The status of the command execution.
*/
int execute_shell_command(char *command)
{
    pid_t pid = fork();
    int status = 0;
    int i = 0;
    char *token;
    char *args[MAX_COMMAND_LENGTH];

    token = strtok(command, " ");
    while (token != NULL)
    {
        args[i] = token;
        token = strtok(NULL, " ");
        i++;
    }
    args[i] = NULL;
    if (pid < 0)
    {
        perror("fork");
        free(command);
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) /* Child Process HERE */
    {
        if (execvp(args[0], args) < 0)
        {
            perror(args[0]);
            free(command);
            exit(2);
        }
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    return status;
}


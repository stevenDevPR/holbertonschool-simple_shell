#include "main.h"

/**
 * shell_main - the main function of the shell program.
 *
 * Return: 0 on success.
**/


int main()
{
    char *command = NULL;
    int status = 0;
    int has_whitespace_check = 1;

    while (1)
    {
        char **argv;

        while (has_whitespace_check == 1)
        {
            command = get_user_input();
            has_whitespace_check = has_whitespace(command);

            if (has_whitespace_check == 1 || command == NULL)
            {
                free(command);
            }
        }
        argv = tokenize_command(command);

        if (argv != NULL && argv[0] != NULL)
        {
            if (strcmp(argv[0], "exit") == 0)
            {
                free_tokenized_arguments(argv);
                free(command);
                exit(EXIT_SUCCESS);
            }
            else
            {
                status = execute_shell_command(*argv); /**Dereference argv to pass correct argument*/
            }
        }
        free_tokenized_arguments(argv);
        free(command);
        has_whitespace_check = 1;
    }
    return status;
}
/**
 * get_user_input - reads a command from the user input.
 *
 * Return: a pointer to the buffer where the command is stored.
**/
char *get_user_input()
{
    char *command = NULL;
    char **argv, *display_command;
    size_t buffer_size = 0;
    ssize_t bytes_read;

    /** Read the command line*/
    bytes_read = getline(&command, &buffer_size, stdin);
    if (bytes_read == -1)
    {
        if (isatty(STDIN_FILENO))
        {
            perror("getline");
            return NULL;
        }
        free(command);
        exit(EXIT_SUCCESS);
    }

    /**Remove the trailing newline character*/
    if (bytes_read > 0 && command[bytes_read - 1] == '\n')
    {
        command[bytes_read - 1] = '\0';
        bytes_read--; /** Adjust the length*/
    }

    /**Tokenize the command*/
    argv = tokenize_command(command);

    /*Concatenate the arguments into a single string for display*/
    display_command = concatenate_arguments(argv);

    /**Free the memory allocated for the tokenized arguments*/
    free_tokenized_arguments(argv);

    /**Free the original command*/
    free(command);

    return display_command;
}
/**
 * has_whitespace - checks if whitespace is present in the command.
 * @command: the command to check for whitespace.
 *
 * Return: 1 if whitespace is present, 0 otherwise.
**/
int has_whitespace(char *command)
{
    int index;

    for (index = 0; command[index] != '\0'; index++)
    {
        if (command[index] != ' ')
        {
            if (command[index] == '\0')
            {
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 1;
}

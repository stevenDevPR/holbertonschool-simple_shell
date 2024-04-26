#include "main.h"
#include <stdlib.h>

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
 * display_shell_prompt - displays the shell prompt.
*/
void display_shell_prompt(void)
{
    printf(">>>> ");
    fflush(stdout);
}
/**
 * tokenize_command - Tokenizes a command string.
 * @command: The command string to tokenize.
 *
 * Return: An array of tokens.
 */
char **tokenize_command(const char *command) {
    char **tokens = malloc(sizeof(char *) * 32); // Assuming max 32 tokens
    if (tokens == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    char *token;
    int token_count = 0;
    int in_quote = 0;
       const char *whitespace = " \t\n\r";

    token = strtok(command, whitespace);
    while (token != NULL) {
        // Check for quotes
        if (token[0] == '"') {
            in_quote = 1;
            // Skip the leading quote
            token++;
        }

        if (in_quote) {
            // Concatenate tokens until closing quote is found
            while (token[strlen(token) - 1] != '"') {
                strcat(tokens[token_count], " ");
                strcat(tokens[token_count], token);
                token = strtok(NULL, whitespace);
            }
            // Add token with closing quote
            strcat(tokens[token_count], " ");
            strcat(tokens[token_count], token);
            in_quote = 0;
        } else {
            tokens[token_count] = strdup(token);
        }

        token = strtok(NULL, whitespace);
        token_count++;
    }
    tokens[token_count] = NULL;

    return tokens;
}
void free_tokenized_arguments(char **argv)
{
	int i;
    /** Free each token and then the array itself*/
    for (i = 0; argv[i] != NULL; i++)
    {
        free(argv[i]);
    }
    free(argv);
}
char *concatenate_arguments(char **argv)
{
    int total_length = 0;
    int i, j, k = 0;
    char *result;

    /* Calculate the total length of the concatenated string */
    for (i = 0; argv[i] != NULL; i++)
    {
        total_length += strlen(argv[i]);
    }

    /* Allocate memory for the concatenated string */
    result = malloc(total_length + 1); /* +1 for the null terminator */
    if (result == NULL)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    /* Copy each string from argv to the concatenated string */
    for (i = 0; argv[i] != NULL; i++)
    {
        for (j = 0; argv[i][j] != '\0'; j++)
        {
            result[k++] = argv[i][j];
        }
    }

    /* Add null terminator to the end of the concatenated string */
    result[k] = '\0';

    return result;
}

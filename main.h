#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

#define MAX_COMMAND_LENGTH 100

void display_shell_prompt(void);
char *get_user_input(void);
int has_whitespace(char *command);
int execute_shell_command(char *command);
int main(void);
void free_tokenized_arguments(char **argv);
char *concatenate_arguments(char **argv);
char **tokenize_command(const char *command);
#endif

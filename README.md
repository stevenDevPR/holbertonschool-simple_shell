# Simple Shell Holberton

## Background Context

This project involves the development of a simple UNIX command interpreter, also known as a shell. The shell is capable of interpreting and executing basic commands entered by the user in a UNIX-like operating system environment.
## Features

- **Command Execution:** Execute a wide range of UNIX commands, such as `ls`, `cd`, `pwd`, `mkdir`, `rm`, etc.
- **Command Line Editing:** Support for basic command line editing functionalities like cursor movement, editing, and history.
- **Environment Variables:** Ability to handle environment variables and substitution.
- **Redirection and Pipes:** Support for input/output redirection and piping of commands.
- **Scripting:** Basic scripting capabilities through the use of shell scripts.

## Installation

To run the command interpreter, follow these steps:

1. Clone the repository: 
`git@github.com:stevenDevPR/holbertonschool-simple_shell.git`
2. Navigate to the project directory: `cd holbertonschool-simple_shell`
3. Compile the source code:`gcc -o shell simple-shell.c` 
4. Run the command interpreter:`./shell`
5. Run Commands ![Shell gif](https://miro.medium.com/v2/resize:fit:1200/1*lqEaA1-6gGQhdLS3k8X0xw.gif)

## Simple Shell

The initial version of the shell, Simple Shell, provides basic functionality as follows:

- Display a prompt and wait for the user to type a command. The command line always ends with a new line.
- The prompt is displayed again each time a command has been executed.
- The command lines are simple, consisting of only one word. No arguments are passed to programs.
- If an executable cannot be found, an error message is printed, and the prompt is displayed again.
- Handles errors and the "end of file" condition (Ctrl+D).
- Building upon Simple Shell 0.1, Simple Shell 0.2 introduces the ability to handle command lines with arguments.
- In Simple Shell 0.3, the following enhancements are made:
- Handles the PATH to locate executables.
- Ensures that `fork` is not called if the command doesn’t exist.
- Implements the `exit` built-in, allowing the user to exit the shell.
- Simple Shell 0.4 adds the implementation of the `env` built-in, which prints the current environment.

## Authors

- Kryss Babilonia
- Steven Bonilla



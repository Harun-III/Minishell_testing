# MiniShell
This project is a simple UNIX shell implemented in C.

## Builtins
The shell should implement the following builtins:

- `echo` with the `-n` option
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

## Features
The shell incorporates the following features:
- Displays a prompt "minishell$ " and waits for a new command.
- Has a working history.
- Finds and launches executables using the PATH variable or an absolute path.
- Handles ' (single) and " (double) quotes like in bash.
- Implements redirections such as:
	- `<` for redirecting input.
	- `>` for redirecting output.
	- `<<` for heredoc (doesn't affect history).
	- `>>` for redirecting output in append mode.
- Implements `|` for pipes.
- Handles environment variables.
- Handles `$?`.
- Behaves like bash for ctrl-C, ctrl-D, and ctrl-\.


## Parts of a Shell Program
The Parser, The Executor, and Shell Subsystems.

## Program Overview:
1. The program will start by reading the input.
2. The input will be parsed into tokens.
	- Example: `echo -n hello > file.txt` will be parsed into 5 tokens: `["echo", "-n", "hello", ">", "file.txt"]`.
3. The tokens will be used to create commands.
	- Example: `echo -n hello > file.txt` will be parsed into 1 command: `["echo", ["-n", "hello"], [">", "file.txt"]]`.
4. The commands will be executed.
	- So basically: lexer -> parser -> executor.

So, first:
- The program will launch without taking any arguments.
- We will read a line from the input using `readline`.
- Then we will use a lexer to tokenize the input.
  - Example: At this part, we will have: `["echo", "-n", "hello", ">", "file.txt"]`.
  - The `t_token` structure will have the following fields:
	 ```c
	 typedef struct s_token
	 {
		  t_join join; // enum JOINABLE, NON_JOINABLE
		  t_state state; // enum DEFAULT, IN_SINGLE, IN_DOUBLE, DOLLAR
		  t_type type; // enum IN, OUT, HERE, APPEND, ERROR, WORD, PIPE
		  t_data data; // struct s_data (see below)
		  struct s_token *next;
	 } t_token;

	 struct s_data
	 {
		  int fd;
		  char *token_data;
	 };
	 ```
- Then we will use a parser to create commands.
  - Example: At this part, we will have a `t_token` linked list with the following tokens:
	 `["echo", "-n", "hello", ">", "file.txt"]`
	 - The parser will loop through the tokens and create commands.
	 - It will separate the commands by the pipe token.
	 - Each command will be a linked list of `t_cmd`.
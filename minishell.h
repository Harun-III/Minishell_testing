/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 03:27:15 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/31 14:10:52 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h> 
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>

/*
** ANSI Escape Sequences for Bold Text Colors
** Usage:
**	printf(R "This is red text." RST);
** Remember to use RST to reset the color after setting it.
*/
# define RST		"\033[0m"	 /* Reset */
# define RED		"\033[1;31m" /* Bold Red */
# define GREEN	"\033[1;32m" /* Bold Green */
# define YELLOW	"\033[1;33m" /* Bold Yellow */
# define BLUE	"\033[1;34m" /* Bold Blue */
# define M		"\033[1;35m" /* Bold Magenta */
# define C		"\033[1;36m" /* Bold Cyan */
# define W		"\033[1;37m" /* Bold White */

# define NOT_VALID  "': not a valid identifier\n"
# define EXPORT_ER  "minishell: export: `"
# define ER_EMPTY_NOT_FOUND "minishell: : command not found"
# define STR_NO_FILE_OR_DIR ": No such file or directory\n"
# define ERR_NO_F_OR_D "minishell: : No such file or directory"
# define ERR_NESTED_SHELL "Error: Nested minishell execution is not allowed\n"

/**** Allocation needs ****/
typedef struct s_mem
{
	void			*ptr;
	struct s_mem	*next;
}				t_mem;
/*****************************/

# define EXPORTED_WITHOUT_EQUAL 0
# define EXPORTED_WITH_EQUAL 1

/**** Allocation needs ****/
int	g_received_signal;

# define SET_EXIT_STATUS 1
# define GET_EXIT_STATUS 0
# define INIT_SIG_HEREDOC 1
# define INIT_SIG_MAIN 0

void	init_signals(int received_signal);
void	heredoc_sig_handler(int signum);
void	sig_quit_handler(int signum);
void	sig_int_handler(int signum);
/*****************************/
/**** Structures and enums ****/
typedef enum e_builtin_status
{
	EXIT_MISUSE = 2,
	EXIT_CANNOT_EXECUTE = 126,
	EXIT_COMMAND_NOT_FOUND = 127,
	EXIT_INVALID_EXIT_ARG = 255
}				t_builtin_status;

/*****************************/
/*struct stat buffer;*/
/*****************************/
typedef enum e_type
{
	IN,
	OUT,
	HERE,
	APPEND,
	ERROR,
	WORD,
	PIPE
}			t_type;

typedef enum e_state
{
	DEFAULT,
	IN_SINGALE,
	IN_DOUBLE,
	DOLLAR
}			t_state;

typedef enum e_joinble
{
	JOINBLE,
	NON_JOINBLE
}			t_join;

typedef struct s_token_data
{
	int		fd;
	char	*origin;
	char	*content;
	t_type	type_fd;
}	t_data;

typedef struct s_token
{
	t_join			join;
	t_state			state;
	t_type			type;
	t_data			data;
	struct s_token	*next;
}				t_token;

typedef struct s_redir
{
	int				fd;	
	char			*file;
	t_type			type;
	struct s_redir	*next;
}				t_redir;

/*
** t_env this type 
** is create and used to manipulate the env
** @var is what is before the '=' 
** @value is what is after the '='
*/
typedef struct s_env
{
	char			*var;
	char			*value;
	int				exported_with_equals;
	struct s_env	*next;
}				t_env;

/*
** This is the Command type
** as the name sugyests it will hold
** the commands before the processing
** @type: a builtin or not
** @cmd : the command
** @arg : the arguments
*/
typedef struct s_cmd
{
	bool			type;
	char			*cmd;
	char			**args;
	t_redir			*redir;
	struct s_cmd	*next;
}				t_cmd;


typedef struct s_shell
{
	int			return_value;

	t_mem *manager;
	t_cmd			*cmd_list;
	t_env			*my_env;
}				t_shell;

int     get_set_return(int value, int flag_set_or_get);
/****************Rida's file these need a revision ***********/
/*############## create_token_utils.c  ###############*/
int create_shell(t_token *tokens , t_shell **the_shell);
int check_syntax_error(t_token *tokens);
int check_fd(t_token *tokens) ;
int open_file(const char *filename, int flags);

int cr_shell(t_shell **shells, t_cmd *cmd_list);

int create_token(char *line, t_shell **the_shell);
int add_token(t_token **tokens, t_join join, t_state state, t_type type, int fd, char *origin ,t_mem **manager);

t_cmd *cr_cmd( bool type, const char *cmd, char **args, t_redir *redir, t_mem **manager);
void add_back_cmd(t_cmd **head, t_cmd *new_cmd);

t_redir	*cr_redir(int fd, const char *file, t_type type, t_mem **manager);
void add_back_redir(t_redir **head, t_redir *new_redir);

void print_all_tokens(t_token *head);
void print_cmd(t_cmd *cmd);
size_t count_tokens(t_token *head);
size_t count_char_array(char **array);
/*############## create_token_utils.c  ###############*/
int	handle_token(char *line, int *i, t_token **tokens, t_mem **manager);

/*############## create_token_utils_1.c  ###############*/
bool	is_space(int c);
int		oxe1(char *str, int *i, t_token **tokens, t_mem **manager);
int		oxe2(char *str, int *i, t_token **tokens, t_mem **manager);
int		ft_allocate(t_token **tokens, char **token, char *str, t_type type, t_mem **manager);

/*############## create_shell_utils.c  ###############*/
int		is_builtin(char *str);
int		is_redirec(t_token *tok, char *cmd);
void	remove_file(char **arg);
t_redir *handle_redirec(t_token *cp, char *cmd, t_mem **mana);
char	*create_arg(t_token *tokens, t_mem **manager, t_shell *the_shell);

/*############## create_shell_utils_1.c  ###############*/
char	**fix_command(char **cmd);

/*############## expanding.c  ###############*/
char	*expand_token_data(t_token *tokens, t_shell *the_shell, t_mem **manager);

/*############## ft_signal.c  ###############*/
// void init_signal();
/*****************************************************/

/****** The builtins Dir *******/
int		builtin_echo(char **args);
int		builtin_cd(char **args, t_env **my_env);
int		builtin_pwd(void);
/* builtin_export */
void	handle_normal_assignment(t_env **my_env, const char *var, \
		const char *value);
void	handle_export_without_equals(t_env **my_env, const char *arg);
int		handle_export(char *arg, t_env **my_env);
void	builtin_export(char **args, t_env **my_env);
/* export_utils.c */
int		count_env(t_env *env);
void	swap(t_env **a, t_env **b);
void	add_or_update_env_var(t_env **env, const char *var,	\
		const char *value, int exported_with_equals);
void	handle_append_operation(t_env **my_env, const char *var, \
		const char *value);
/* export_env_utils.c */
void	sort_env_array(t_env **env_array, int size);
t_env	*find_env_var(t_env *env, const char *var);
void	print_sorted_env(t_env **env_array, int size);
t_env	*create_env_node(const char *var, const char *value, \
		int exported_with_equals);
void	update_env_var(t_env *existing, const char *value, \
	int exported_with_equals);

int		builtin_unset(char **args, t_env **my_env, int *exit_status);
int		builtin_env(t_env *env);
int		builtin_exit(char **args, t_shell *the_shell);
bool	check_if_arg_is_valid(char *arg);

// void    process_commands(t_shell *shell);
/*****************************/

/****** Misc. files *******/
void	cleanup_at_exit(t_shell *the_shell);
void	init_shell(t_shell *the_shell, char **env, t_mem *manager);

/**** 		env			 ****/
void	print_env(t_env *env);
t_env	*initialize_env(char **env);
void	_free_env(t_env **env);
/*****************************/

/****** The execution Dir *******/
/* execution/env_to_array.c */
char	**env_to_array(t_env *env);
/* execution/exec_utils.c */
char	*get_env_value(t_env *env, const char *var_name);
char	*find_command_path(t_shell *shell, const char *cmd);
int		count_commands(t_cmd *cmd);
/* execution/execute_builtin.c */
int		execute_builtin(t_shell *shell, t_cmd *cmd);
/* execution/execute_external.c */
int		execute_external(t_shell *shell, t_cmd *cmd);
/* execution/execution.c */
void	setup_child_process(int prev_pipe, int *pipefd, t_cmd *cmd);
void	handle_parent_process(int *prev_pipe, int *pipefd, t_cmd *cmd);
/* execution/setup_redirections.c */
int		setup_redirections(t_redir *redir);
void	clean_file_descriptors(void);
/* execution/exec_utils.c */
void	norm_case_1(t_cmd *cmd);
char	*concat_with_slash(const char *dir, const char *cmd);
void	execute_child_process(t_shell *shell, t_cmd *cmd);
void	execute_builtin_command(t_shell *shell, t_cmd *cmd);
void	wait_for_children(pid_t *child_pids, int cmd_count);
void	execute_external_command(t_shell *shell, t_cmd *cmd);
void	execute_command(t_shell *shell, t_cmd *cmd);
bool	has_nested_minishell(t_cmd *cmd);
bool	is_minishell(const char *cmd);
/*******************************/

/*  main_utils */
int		add_to_hitory_creat_token(char **line, t_shell **the_shell);
void	exec_clean_up_reset_signal(t_shell **the_shell);
void	int_in_main(t_shell **the_shell, t_mem **mem, char **env);
void	handle_null_in_main(t_shell *the_shell);
void	cleanup_at_exit(t_shell *the_shell);

/**** 		execution			 ****/
int		execute_pipeline(t_shell *shell, t_cmd *cmd);
/*****************************/

/**** Allocation needs ****/
void	*my_malloc(t_mem** manager, size_t size);
void	my_free(t_mem** manager, void* ptr);
void	cleanup(t_mem** manager);
/*****************************/

/******* string tools ********/

int		ft_lstsize(t_token *lst);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, const char *src);
void	ft_sandwitch_err(char *bread1, char *meat, char *bread2);
char	*ft_strdup_mm(t_mem **manager,const char *s1);
char	*ft_strndup_mm(t_mem **manager, const char *s, size_t n);
char	*ft_strjoin_mm(t_mem **manager,char const *s1, char const *s2);
char	**ft_split_mm(t_mem **manager,char const *s, char c);
char	*ft_strtok(char *str, const char *delim);
int		ft_lstsize(t_token *lst);

/*****************************/

#endif
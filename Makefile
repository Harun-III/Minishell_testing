# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/12 03:23:16 by rbouizer          #+#    #+#              #
#    Updated: 2024/10/31 09:13:28 by eghalime         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This make file needs revision
# also check the makefile in libft folder
SRCS =	parsing/create_token.c \
		parsing/create_token_utils.c \
		parsing/create_token_utils_1.c \
		parsing/create_shell.c \
		parsing/create_shell_utils.c \
		parsing/create_shell_utils_1.c \
		parsing/expanding.c \
		parsing/add_node.c \
		parsing/add_node_utils.c \
		parsing/syntax_error.c \
		parsing/utlis.c \
		parsing/here_doc.c \
		src/main_utils.c \
		src/main.c \
		init/init_t_shell.c \
		builtins/builtin_cd.c \
		builtins/builtin_echo.c \
		builtins/builtin_env.c \
		builtins/builtin_exit.c \
		builtins/builtin_export.c \
		builtins/builtin_pwd.c \
		builtins/builtin_unset.c \
		builtins/builtin_utils.c \
		builtins/export_env_utils.c \
		builtins/export_utils.c \
		env/inti_env.c \
		env/print_env.c \
		execution/env_to_array.c \
		execution/exec_utils.c \
		execution/exec_utils_2.c \
		execution/exec_utils_3.c \
		execution/exec_utils_4.c \
		execution/execute_builtin.c \
		execution/execution.c \
		execution/setup_redirections.c \
		memroy_management/memory_managment.c \
		strings_tools/ft_sandwith.c \
		strings_tools/ft_strcat.c \
		strings_tools/ft_strcpy.c \
		strings_tools/ft_strdup_mm.c \
		strings_tools/ft_split_mm.c \
		strings_tools/ft_strndup_mm.c \
		strings_tools/ft_strjoin_mm.c \
		strings_tools/ft_lstsize.c \
		strings_tools/ft_strtok.c \
		signals/signals.c \
00_sandbox_test/check_t_shell.c

OBJS = $(SRCS:.c=.o)

# CFLAGS = -Wall -Wextra -Werror -fsanitize=address
LDFLAGS = $(shell brew --prefix readline)
CFLAGS = -Wall -Wextra -Werror -g -I $(LDFLAGS)/include #-fsanitize=address

LIBFT = libft/libft.a

CC = cc
RM = rm -rf

NAME = minishell


all: $(NAME)

$(NAME): $(OBJS) 
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline -L $(LDFLAGS)/lib 

%.o: %.c minishell.h libft.h
	$(CC) $(CFLAGS) -c $< -o $@ 

clean:
	make clean -C libft
	$(RM) $(OBJS)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind --leak-check=full ./$(NAME)

.PHONY: all clean fclean re valgrind

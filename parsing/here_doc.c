/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:26:10 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/30 17:55:13 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_file(const char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror("Error opening file");
		return (-1);
	}
	return (fd);
}

static int	here_doc_child_process(int fd, const char *delimiter)
{
	char	*li;
	ssize_t	result;

	init_signals(INIT_SIG_HEREDOC);
	while (1)
	{
		li = readline("> ");
		if (!li)
		{
			close(fd);
			exit(130);
		}
		if (ft_strcmp(li, delimiter) == 0)
		{
			free(li);
			close(fd);
			exit(0);
		}
		result = write(fd, li, strlen(li));
		write(fd, "\n", 1);
		free(li);
	}
}

int	handle_here_doc(t_token *token)
{
	int				fd;
	pid_t			pid;
	int				status;
	struct termios	or;
	char			*del;

	while (token->next && ft_strcmp(token->next->data.origin, "\0") == 0)
		token = token->next;
	del = token->next->data.origin;
	fd = open_file("here_doc", O_RDWR | O_CREAT | O_TRUNC);
	if (!token->next || !del || fd == -1)
		return (0);
	(1) && (token->data.fd = fd, token->data.type_fd = token->type);
	(2) && (tcgetattr(STDIN_FILENO, &or), pid = fork());
	if (pid == -1)
		return (close(fd), 0);
	if (pid == 0)
		here_doc_child_process(fd, del);
	(2) && (waitpid(pid, &status, 0), tcsetattr(STDIN_FILENO, TCSANOW, &or));
	if (g_received_signal == 0)
		get_set_return(WEXITSTATUS(status), SET_EXIT_STATUS);
	else
		return (close(fd), unlink("here_doc"), 0);
	return (1);
}

int	handle_token_pro(t_token *current)
{
	if (current->type == HERE)
		return (handle_here_doc(current));
	return (1);
}

int	check_fd(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (!handle_token_pro(current))
			return (0);
		current = current->next;
	}
	return (1);
}

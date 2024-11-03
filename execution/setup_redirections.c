/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:09:06 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 18:38:04 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#define OPEN_MAX_FD 10240

void	clean_file_descriptors(void)
{
	int	i;

	i = 3;
	while (i < OPEN_MAX_FD)
	{
		close(i);
		i++;
	}
}

static int	hand_here_doc_in_execution(int here_fd)
{
	close(here_fd);
	here_fd = open("here_doc", O_RDONLY);
	if (here_fd == -1)
	{
		perror("open heredoc");
		return (1);
	}
	if (dup2(here_fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		return (1);
	}
	close(here_fd);
	return (0);
}

static void	set_flags_and_targetfd(t_type fd_type, int *target_fd, int *flags)
{
	if (fd_type == IN)
	{
		*flags = O_RDONLY;
		*target_fd = STDIN_FILENO;
	}
	else if (fd_type == OUT)
	{
		*flags = O_WRONLY | O_CREAT | O_TRUNC;
		*target_fd = STDOUT_FILENO;
	}
	else if (fd_type == APPEND)
	{
		*flags = O_WRONLY | O_CREAT | O_APPEND;
		*target_fd = STDOUT_FILENO;
	}
}

int	setup_redirections(t_redir *redir)
{
	int	flags;
	int	target_fd;
	int	fd;

	while (redir)
	{
		if (redir->type == HERE)
		{
			if (hand_here_doc_in_execution(redir->fd) == 1)
				return (1);
			redir = redir->next;
			continue ;
		}
		set_flags_and_targetfd (redir->type, &target_fd, &flags);
		if (!redir->file || !redir->file[0])
			return (ft_putendl_fd(ERR_NO_F_OR_D, 2), 1);
		fd = open(redir->file, flags, 0644);
		if (fd == -1)
			return (perror("open"), 1);
		if (dup2(fd, target_fd) == -1)
			return (perror("dup2"), close (fd), 1);
		close(fd);
		redir = redir->next;
	}
	return (0);
}

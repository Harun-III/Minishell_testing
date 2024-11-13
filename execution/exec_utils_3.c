/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:49:59 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/12 22:30:20 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	setup_child_process(int prev_pipe, int *pipefd, t_cmd *cmd)
{
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (cmd->next)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	if (setup_redirections(cmd->redir) == 1)
		exit (1);
}

void	execute_builtin_command(t_shell *shell, t_cmd *cmd)
{
	int	stdin_copy;
	int	stdout_copy;
	int	exit_status;

	stdin_copy = dup(STDIN_FILENO);
	stdout_copy = dup(STDOUT_FILENO);
	if (setup_redirections(cmd->redir) == -2)
	{
		get_set_return(1, 1);
		return ;
	}
	exit_status = execute_builtin(shell, cmd);
	if (g_received_signal == 0)
		get_set_return(exit_status, 1);
	dup2(stdin_copy, STDIN_FILENO);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdin_copy);
	close(stdout_copy);
}

void	wait_for_children(pid_t *child_pids, int cmd_count)
{
	int	i;
	int	status;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(child_pids[i], &status, 0);
		if (i == cmd_count - 1 && g_received_signal == 0)
			get_set_return(WEXITSTATUS(status), SET_EXIT_STATUS);
		i++;
	}
}

bool	is_minishell(const char *cmd)
{
	const char	*base_cmd;

	base_cmd = cmd;
	if (!cmd)
		return (false);
	while (*cmd)
	{
		if (*cmd == '/')
			base_cmd = cmd + 1;
		cmd++;
	}
	if (ft_strcmp(base_cmd, "minishell") == 0)
		return (true);
	return (false);
}

bool	has_nested_minishell(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (is_minishell(current->cmd))
			return (true);
		current = current->next;
	}
	return (false);
}

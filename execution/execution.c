/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:16:18 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/28 09:15:03 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_parent_process(int *prev_pipe, int *pipefd, t_cmd *cmd)
{
	if (*prev_pipe != STDIN_FILENO)
		close(*prev_pipe);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_pipe = pipefd[0];
	}
}

static void	handle_child(int *prev_pipe, int *pipefd,
		t_shell *shell, t_cmd *cmd)
{
	setup_child_process(*prev_pipe, pipefd, cmd);
	execute_child_process(shell, cmd);
}

int	create_pipes_and_fork(t_shell *shell, t_cmd *cmd, pid_t *child_pids)
{
	int		prev_pipe;
	int		cmd_index;
	int		pipefd[2];
	pid_t	pid;

	(1) && (prev_pipe = STDIN_FILENO, cmd_index = 0);
	while (cmd)
	{
		if (cmd->next && pipe(pipefd) == -1)
			return ((perror("pipe"), -1));
		pid = fork();
		if (pid == 0)
			free((handle_child(&prev_pipe, pipefd, shell, cmd), child_pids));
		else if (pid < 0)
		{
			if (cmd->next)
				(1) && (close(pipefd[0]), close(pipefd[1]));
			return ((perror("fork"), -1));
		}
		child_pids[cmd_index] = pid;
		handle_parent_process(&prev_pipe, pipefd, cmd);
		cmd = ((cmd_index++, cmd->next));
	}
	return (0);
}

void	execute_single_command(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type)
		execute_builtin_command(shell, cmd);
	else
		execute_external_command(shell, cmd);
}

int	execute_pipeline(t_shell *shell, t_cmd *cmd)
{
	pid_t	*child_pids;
	int		cmd_count;

	cmd_count = count_commands(cmd);
	if (cmd_count == 1)
	{
		if (ft_strcmp(cmd->args[0], "exit") == 0)
			ft_putstr_fd("exit\n", 2);
		execute_single_command(shell, cmd);
		return (0);
	}
	if (has_nested_minishell(cmd))
	{
		ft_putstr_fd(ERR_NESTED_SHELL, 2);
		return (-1);
	}
	child_pids = malloc(sizeof(pid_t) * cmd_count);
	if (!child_pids)
		return (perror("malloc"), -1);
	if (create_pipes_and_fork(shell, cmd, child_pids) == -1)
		return (free(child_pids), -1);
	wait_for_children(child_pids, cmd_count);
	free(child_pids);
	return (0);
}

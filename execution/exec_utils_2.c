/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:30:23 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 18:37:51 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_external_command(t_shell *shell, t_cmd *cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (setup_redirections(cmd->redir) == 1)
			exit (1);
		execute_command(shell, cmd);
	}
	else if (pid < 0)
	{
		perror("fork");
		return ;
	}
	waitpid(pid, &status, 0);
	if (g_received_signal == 0)
		get_set_return(WEXITSTATUS(status), 1);
}

static void	handle_absolute_and_explicit_relative(t_shell *shell, t_cmd *cmd)
{
	struct stat	path_stat;

	if (stat(cmd->cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
	{
		ft_sandwitch_err("Minishell: ", cmd->cmd, " is a directory\n");
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	if (access(cmd->cmd, X_OK) == 0)
	{
		execve(cmd->cmd, cmd->args, env_to_array(shell->my_env));
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		ft_sandwitch_err("Minishell: ", cmd->cmd, STR_NO_FILE_OR_DIR);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
}

static void	handle_path_command(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = find_command_path(shell, cmd->cmd);
	if (!path)
	{
		ft_sandwitch_err("Command not found: ", cmd->cmd, "\n");
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	execve(path, cmd->args, env_to_array(shell->my_env));
	perror("execve");
	exit((free(path), EXIT_FAILURE));
}

static void	handle_relative_path(t_shell *shell, t_cmd *cmd)
{
	struct stat	path_stat;

	if (ft_strchr(cmd->cmd, '/'))
	{
		if (stat(cmd->cmd, &path_stat) == 0 && S_ISDIR(path_stat.st_mode))
		{
			ft_sandwitch_err("Minishell: ", cmd->cmd, " is a directory\n");
			exit(EXIT_COMMAND_NOT_FOUND);
		}
		if (access(cmd->cmd, X_OK) == 0)
		{
			execve(cmd->cmd, cmd->args, env_to_array(shell->my_env));
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			ft_sandwitch_err("Minishell: ", cmd->cmd, STR_NO_FILE_OR_DIR);
			exit(EXIT_COMMAND_NOT_FOUND);
		}
	}
}

/*
	cases:
		no com	+	redir		(e.g.$ >> asdf)
		com		+	redir		(e.g.$ ls >> hh)
		com		+	no redir 	(e.g.$ ls)
*/
void	execute_command(t_shell *shell, t_cmd *cmd)
{
	if (!cmd->cmd && cmd->redir)
		norm_case_1(cmd);
	if ((cmd->cmd == NULL || cmd->cmd[0] == '\0') && cmd->redir)
	{
		setup_redirections(cmd->redir);
		ft_putendl_fd(ER_EMPTY_NOT_FOUND, 2);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	if ((cmd->cmd == NULL || cmd->cmd[0] == '\0') && !cmd->redir)
		exit((ft_putendl_fd(ER_EMPTY_NOT_FOUND, 2), EXIT_COMMAND_NOT_FOUND));
	if (cmd->cmd[0] == '/' || ft_strncmp(cmd->cmd, "./", 2) == 0
		|| ft_strncmp(cmd->cmd, "../", 3) == 0)
	{
		handle_absolute_and_explicit_relative(shell, cmd);
		exit(EXIT_COMMAND_NOT_FOUND);
	}
	if (cmd->cmd[0] == '.' || ft_strncmp(cmd->cmd, "..", 2) == 0)
	{
		ft_sandwitch_err ("bash: ", cmd->cmd, ": command not found\n");
		exit(EXIT_CANNOT_EXECUTE);
	}
	handle_relative_path(shell, cmd);
	handle_path_command(shell, cmd);
	ft_putendl_fd("minishell: command not found", 2);
	exit(EXIT_COMMAND_NOT_FOUND);
}

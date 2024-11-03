/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:03:27 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/22 18:32:15 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env_value(t_env *env, const char *var_name)
{
	while (env)
	{
		if (ft_strcmp(env->var, var_name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*concat_with_slash(const char *dir, const char *cmd)
{
	char	*full_path ;
	size_t	len;

	len = ft_strlen(dir) + ft_strlen(cmd) + 2;
	full_path = (char *)malloc(len);
	if (!full_path)
		return (NULL);
	ft_strcpy(full_path, dir);
	full_path[ft_strlen(dir)] = '/';
	ft_strcpy(full_path + ft_strlen(dir) + 1, cmd);
	return (full_path);
}

char	*find_command_path(t_shell *shell, const char *cmd)
{
	char	*full_path;
	char	*path_env;
	char	*path;
	char	*dir;

	path_env = get_env_value(shell->my_env, "PATH");
	if (!path_env)
		return (NULL);
	path = ft_strdup(path_env);
	dir = ft_strtok(path, ":");
	while (dir)
	{
		full_path = concat_with_slash(dir, cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(path);
			return (full_path);
		}
		free(full_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

int	count_commands(t_cmd *cmd)
{
	int		cmd_count;
	t_cmd	*current_cmd;

	cmd_count = 0;
	current_cmd = cmd;
	while (current_cmd)
	{
		cmd_count++;
		current_cmd = current_cmd->next;
	}
	return (cmd_count);
}

void	execute_child_process(t_shell *shell, t_cmd *cmd)
{
	if (cmd->type)
		exit(execute_builtin(shell, cmd));
	else
		execute_command(shell, cmd);
	exit(EXIT_FAILURE);
}

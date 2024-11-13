/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 15:04:41 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/10 23:54:47 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_builtin(t_shell *shell, t_cmd *cmd)
{
	t_env	*my_env;
	int		result;
	int		norm_int;

	result = 0;
	my_env = shell->my_env;
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		result = builtin_echo(cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		result = builtin_env(my_env);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		result = builtin_pwd();
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		result = builtin_exit(cmd->args, shell);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
	{
		builtin_export(cmd->args, &shell->my_env);
		result = get_set_return(0, 0);
	}
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		result = builtin_unset(cmd->args, &(shell->my_env), &norm_int);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		result = builtin_cd(cmd->args, &shell->my_env);
	return (result);
}

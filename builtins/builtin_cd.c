/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:28:26 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/15 18:53:23 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(char **args, t_env **my_env)
{
	char	*path;
	char	old_pwd[PATH_MAX];
	char	new_pwd[PATH_MAX];

	if (getcwd(old_pwd, sizeof(old_pwd)) == NULL)
		return (perror ("getcwd failed"), EXIT_FAILURE);
	if (args[1] == NULL)
	{
		path = get_env_value(*my_env, "HOME");
		if (path == NULL)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
	}
	else
		path = args[1];
	if (chdir(path) != 0)
		return (perror("cd"), EXIT_FAILURE);
	if (getcwd(new_pwd, sizeof(new_pwd)) == NULL)
		return (perror("getcwd"), EXIT_FAILURE);
	add_or_update_env_var(my_env, "OLDPWD", old_pwd, EXPORTED_WITH_EQUAL);
	add_or_update_env_var(my_env, "PWD", new_pwd, EXPORTED_WITH_EQUAL);
	return (EXIT_SUCCESS);
}

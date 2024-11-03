/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:35:07 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/15 18:53:44 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** The args can only contain alphanumeric characters and underscores
*/
bool	check_if_arg_is_valid(char *arg)
{
	int	i;

	i = 0;
	if (!arg[0])
		return (false);
	while (arg[i])
	{
		if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
			return (false);
		if (ft_isalnum(arg[i]) || arg[i] == '_')
			i++;
		else
			return (false);
	}
	return (true);
}

void	handle_normal_assignment(t_env **my_env,
								const char *var, const char *value)
{
	add_or_update_env_var(my_env, var, value, EXPORTED_WITH_EQUAL);
}

void	handle_export_without_equals(t_env **my_env, const char *arg)
{
	t_env	*existing;

	existing = find_env_var(*my_env, arg);
	if (existing)
		existing->exported_with_equals = 0;
	else
		add_or_update_env_var(my_env, arg, "", EXPORTED_WITHOUT_EQUAL);
}

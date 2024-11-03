/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:51:51 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/23 11:22:50 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_env_node(t_env **my_env, t_env *node)
{
	t_env	*current;
	t_env	*prev;

	current = *my_env;
	prev = NULL;
	while (current)
	{
		if (current == node)
		{
			if (prev)
				prev->next = current->next;
			else
				*my_env = current->next;
			free(current->var);
			free(current->value);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

static void	print_error_update_vars(int *exit_status, char *str)
{
	ft_sandwitch_err("minishell: unset: `", str, NOT_VALID);
	*exit_status = EXIT_FAILURE;
}

int	builtin_unset(char **args, t_env **my_env, int *exit_status)
{
	t_env	*current;
	int		i;

	(1) && (*exit_status = EXIT_SUCCESS, i = 0);
	if (!args[1])
		return (EXIT_SUCCESS);
	while (args[++i] != NULL)
	{
		if (!check_if_arg_is_valid(args[i]))
		{
			print_error_update_vars(exit_status, args[i]);
			continue ;
		}
		current = *my_env;
		while (current)
		{
			if (ft_strcmp(current->var, args[i]) == 0)
			{
				delete_env_node(my_env, current);
				break ;
			}
			current = current->next;
		}
	}
	return (*exit_status);
}

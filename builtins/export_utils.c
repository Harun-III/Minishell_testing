/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:32:24 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/15 18:54:13 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Count the number of nodes in the env list 
*/
int	count_env(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

/*
** Function to swap two t_env pointers
*/
void	swap(t_env **a, t_env **b)
{
	t_env	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	add_or_update_env_var(t_env **env, const char *var,
							const char *value, int exported_with_equals)
{
	t_env	*existing;
	t_env	*new_node;

	existing = find_env_var(*env, var);
	if (existing)
		update_env_var(existing, value, exported_with_equals);
	else
	{
		new_node = create_env_node(var, value, exported_with_equals);
		new_node->next = *env;
		*env = new_node;
	}
}

void	handle_append_operation(t_env **my_env,
								const char *var, const char *value)
{
	t_env	*existing;
	char	*new_value;
	size_t	ex_value;

	existing = find_env_var(*my_env, var);
	if (existing)
	{
		ex_value = ft_strlen(existing->value);
		new_value = malloc(ex_value + ft_strlen(value) + 1);
		ft_strcpy(new_value, existing->value);
		ft_strcat(new_value, value);
		update_env_var(existing, new_value, 1);
		free(new_value);
	}
	else
		add_or_update_env_var(my_env, var, value, EXPORTED_WITH_EQUAL);
}

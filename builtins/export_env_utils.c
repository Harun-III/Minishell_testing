/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 09:34:05 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/10 20:58:58 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Bubble sort to sort environment
** variables based on the 'var' field
*/
void	sort_env_array(t_env **env_array, int size)
{
	int	i;
	int	sorted;

	while (1)
	{
		sorted = 1;
		i = 0;
		while (i < size - 1)
		{
			if (ft_strcmp(env_array[i]->var, env_array[i + 1]->var) > 0)
			{
				swap(&env_array[i], &env_array[i + 1]);
				sorted = 0;
			}
			i++;
		}
		if (sorted)
			break ;
	}
}

t_env	*find_env_var(t_env *env, const char *var)
{
	while (env)
	{
		if (ft_strcmp(env->var, var) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	print_sorted_env(t_env **env_array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (env_array[i]->value)
			printf("declare -x %s=\"%s\"\n", \
			env_array[i]->var, env_array[i]->value);
		else
			printf("declare -x %s\n", env_array[i]->var);
		i++;
	}
}

/*
** Function to create a new environment variable node
*/
t_env	*create_env_node(const char *var,
						const char *value, int exported_with_equals)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	new_node->var = ft_strdup(var);
	new_node->value = ft_strdup(value);
	new_node->exported_with_equals = exported_with_equals;
	new_node->next = NULL;
	return (new_node);
}

void	update_env_var(t_env *existing,
					const char *value, int exported_with_equals)
{
	free(existing->value);
	existing->value = ft_strdup(value);
	existing->exported_with_equals = exported_with_equals;
}

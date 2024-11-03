/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_array.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:22:29 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/16 15:47:02 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env_array_if_fail(int nb_nodes, char **env_array)
{
	while (nb_nodes > 0)
	{
		nb_nodes--;
		free(env_array[nb_nodes]);
	}
	free(env_array);
}

/*
** count the number of environment variables
** allocate memory for the array (count + 1 for null terminator)
** allocate memory for "var=value" string
** free previously allocated memory if malloc fails
** create "var=value" string
*/
char	**env_to_array(t_env *env)
{
	int		count;
	t_env	*temp;
	char	**env_array;

	temp = env;
	count = count_env(temp);
	env_array = (char **)malloc(sizeof(char *) * (count + 1));
	if (!env_array)
		return (NULL);
	count = 0;
	while (env)
	{
		env_array[count] = (char *)malloc(ft_strlen(env->var)
				+ ft_strlen(env->value) + 2);
		if (!env_array[count])
			return (free_env_array_if_fail (count, env_array), NULL);
		ft_strcpy(env_array[count], env->var);
		ft_strcat(env_array[count], "=");
		ft_strcat(env_array[count], env->value);
		count++ ;
		env = env->next;
	}
	env_array[count] = NULL;
	return (env_array);
}

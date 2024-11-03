/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inti_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:03:14 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 21:33:26 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env	*create_env_nod(char *env_var)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		new_node->var = ft_strndup(env_var, equal_sign - env_var);
		new_node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_node->var = ft_strdup(env_var);
		new_node->value = NULL;
	}
	new_node->next = NULL;
	return (new_node);
}

t_env	*initialize_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = NULL;
	current = NULL;
	while (*env)
	{
		new_node = create_env_nod(*env);
		if (!new_node)
			return (NULL);
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
		env++;
	}
	return (head);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:03:22 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 21:33:53 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** if the value is NULL then it will print only the var
** $ export var || $ export var=
**     --> var
*/
void	print_env(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s=%s\n", env->var, env->value);
		else
			printf("%s\n", env->var);
		env = env->next;
	}
}

void	_free_env(t_env **env)
{
	t_env	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		free(tmp->var);
		free(tmp->value);
		free(tmp);
	}
	*env = NULL;
}

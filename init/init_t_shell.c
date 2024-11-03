/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_shell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:08:16 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 19:21:58 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	increment_shell_lvl(t_env **my_env)
{
	char	*lvl_value;
	int		new_value;

	lvl_value = get_env_value(*my_env, "SHLVL");
	if (!lvl_value)
		return ;
	new_value = ft_atoi(lvl_value);
	lvl_value = ft_itoa(++new_value);
	if (lvl_value)
		add_or_update_env_var(my_env, "SHLVL", lvl_value, EXPORTED_WITH_EQUAL);
	free (lvl_value);
}

void	init_shell(t_shell *the_shell, char **env, t_mem *mem)
{
	t_env	*my_env;

	g_received_signal = 0;
	my_env = initialize_env(env);
	if (my_env)
		increment_shell_lvl(&my_env);
	g_received_signal = 0;
	if (the_shell && my_env)
	{
		the_shell->my_env = my_env;
		the_shell->manager = mem;
		get_set_return(0, SET_EXIT_STATUS);
	}
	else
	{
		perror ("Inti");
		cleanup_at_exit (the_shell);
		exit (1);
	}
}

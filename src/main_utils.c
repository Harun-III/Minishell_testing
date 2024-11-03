/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:23:23 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 21:25:24 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cleanup_at_exit(t_shell *the_shell)
{
	clean_file_descriptors();
	_free_env(&the_shell->my_env);
	free(the_shell);
}

void	handle_null_in_main(t_shell *the_shell)
{
	write(2, "exit\n", 5);
	builtin_exit((char *[]){NULL, NULL}, the_shell);
}

void	int_in_main(t_shell **the_shell, t_mem **mem, char **env)
{
	*the_shell = malloc(sizeof(t_shell));
	if (!*the_shell)
	{
		ft_putendl_fd("Failed to allocate memory for shell", 2);
		exit(1);
	}
	*mem = NULL;
	init_shell(*the_shell, env, *mem);
	init_signals(INIT_SIG_MAIN);
}

void	exec_clean_up_reset_signal(t_shell **the_shell)
{
	execute_pipeline(*the_shell, (*the_shell)->cmd_list);
	cleanup(&(*the_shell)->manager);
	clean_file_descriptors();
	g_received_signal = 0;
}

int	add_to_hitory_creat_token(char **line, t_shell **the_shell)
{
	add_history(*line);
	if (!create_token(*line, &(*the_shell)))
	{
		cleanup(&(*the_shell)->manager);
		free(*line);
		return (-1);
	}
	return (0);
}

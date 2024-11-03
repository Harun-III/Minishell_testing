/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 17:34:23 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 21:28:10 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_int_handler(int signum)
{
	int	pid;

	(void)signum;
	pid = wait(NULL);
	if (pid <= 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		get_set_return(1, SET_EXIT_STATUS);
	}
	else
	{
		write(1, "\n", 1);
		get_set_return(130, SET_EXIT_STATUS);
		g_received_signal = 1;
	}
}

void	sig_quit_handler(int signum)
{
	int	pid;

	(void)signum;
	pid = wait(NULL);
	if (pid <= 0)
		;
	else
	{
		write(1, "Quit: 3\n", 9);
		get_set_return(130, SET_EXIT_STATUS);
		g_received_signal = 1;
	}
}

void	heredoc_sig_handler(int signum)
{
	int	pid;

	(void)signum;
	pid = wait(NULL);
	if (pid <= 0)
	{
		get_set_return(1, SET_EXIT_STATUS);
		g_received_signal = 1;
		exit(333);
	}
	clean_file_descriptors();
}

void	init_signals(int received_signal)
{
	if (received_signal == INIT_SIG_HEREDOC)
	{
		signal(SIGINT, heredoc_sig_handler);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		rl_catch_signals = 0;
		signal(SIGINT, sig_int_handler);
		signal(SIGQUIT, sig_quit_handler);
	}
}

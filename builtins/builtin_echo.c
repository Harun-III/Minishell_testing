/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:15:27 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/31 11:21:55 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_n_option(const char *arg)
{
	int	j;

	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	j = 1;
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

static int	check_n_options(char **args)
{
	int	i;

	i = 1;
	while (args[i] && is_valid_n_option(args[i]))
		i++;
	return (i - 1);
}

int	builtin_echo(char **args)
{
	int	i;
	int	print_newline;
	int	n_options;

	print_newline = 1;
	n_options = check_n_options(args);
	if (n_options > 0)
	{
		print_newline = 0;
		i = n_options + 1;
	}
	else
		i = 1;
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (print_newline)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}

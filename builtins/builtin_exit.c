/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:21:43 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/12 23:27:23 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool is_valid_number(char *str, long *result)
{
    int i;
    int sign;
    long num;

	(1) && (i = 0, num = 0, sign = 1);
    if (!str || !*str)
        return (false);
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (!str[i] || str[i] == '+' || str[i] == '-')
        return (false);
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (false);
        if (num > LONG_MAX / 10 || 
            (num == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
            return (false);
        (1) && (num = (num * 10) + (str[i] - '0'), i++);
    }
    return (*result = num * sign, true);
}

int	builtin_exit(char **args, t_shell *the_shell)
{
	long	number;
	bool	is_valid;

	if (!args || !args[1])
	{
		cleanup_at_exit(the_shell);
		exit(EXIT_SUCCESS);
	}
	is_valid = is_valid_number(args[1], &number);
	if (!is_valid)
	{
		ft_sandwitch_err("exit: ", args[1], ": numeric argument required\n");
		cleanup_at_exit(the_shell);
		exit(EXIT_INVALID_EXIT_ARG);
	}
	if (args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	cleanup_at_exit(the_shell);
	exit((unsigned char)number);
}

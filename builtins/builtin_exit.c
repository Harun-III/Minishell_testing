/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 14:21:43 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/19 18:34:39 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** why (num > LONG_MAX / 10) ::
**		If num is greater than LONG_MAX / 10, multiplying it 
**		by 10 will definitely result in a number larger than LONG_MAX
**	(num == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
** The (num == LONG_MAX / 10)
**		checks for a boundary, so there is a place for ony one added digit
**	so we check the added digit ("(str[i] - '0') > LONG_MAX % 10)")
*/

static bool	is_valid_number(char *str, long *result)
{
	int		i;
	int		sign;
	long	num;

	i = 0 ;
	num = 0;
	sign = 1;
	if (!str || !*str)
		return (false);
	if (str[i] == '-')
		(1) && (sign = -1, i++);
	if (!str[i])
		return (false);
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (false);
		if (num > LONG_MAX / 10
			|| (num == LONG_MAX / 10 && (str[i] - '0') > LONG_MAX % 10))
			return (false);
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	*result = num * sign;
	return (true);
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

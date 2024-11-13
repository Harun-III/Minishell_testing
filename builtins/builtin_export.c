/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 15:04:20 by eghalime          #+#    #+#             */
/*   Updated: 2024/11/11 00:46:42 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** dafp = dubed_arg_for_print
*/
int	handle_with_equal(char *arg, char *equal_sign, t_env **my_env, char *dafp)
{
	char	*var;
	char	*value;
	int		is_append;

	(1) && (is_append = 0, *equal_sign = '\0', var = arg);
	value = equal_sign + 1;
	if (equal_sign > arg && *(equal_sign - 1) == '+')
	{
		is_append = 1;
		*(equal_sign - 1) = '\0';
	}
	if (check_if_arg_is_valid(var))
	{
		if (is_append)
			handle_append_operation(my_env, var, value);
		else
			handle_normal_assignment(my_env, var, value);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_sandwitch_err(EXPORT_ER, dafp, NOT_VALID);
		return (EXIT_FAILURE);
	}
}

int	handle_without_equal(char *arg, t_env **my_env, char *dubed_arg_for_print)
{
	if (check_if_arg_is_valid(arg))
	{
		handle_export_without_equals(my_env, arg);
		return (EXIT_SUCCESS);
	}
	else
	{
		ft_sandwitch_err(EXPORT_ER, dubed_arg_for_print, NOT_VALID);
		return (EXIT_FAILURE);
	}
}

int	handle_export(char *arg, t_env **my_env)
{
	char	*equal_sign;
	char	*dubed_arg_for_print;
	int		exit_value;

	dubed_arg_for_print = ft_strdup(arg);
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		exit_value = handle_with_equal(arg, equal_sign, my_env,
				dubed_arg_for_print);
	else
		exit_value = handle_without_equal(arg, my_env, dubed_arg_for_print);
	free(dubed_arg_for_print);
	return (exit_value);
}

void	print_sorted_environment(t_env **my_env)
{
	int		env_count;
	int		i;
	t_env	**env_array;
	t_env	*temp;

	env_count = count_env(*my_env);
	env_array = malloc(sizeof(t_env *) * env_count);
	if (!env_array)
	{
		get_set_return(EXIT_FAILURE, 1);
		return ;
	}
	i = 0;
	temp = *my_env;
	while (temp)
	{
		env_array[i++] = temp;
		temp = temp->next;
	}
	sort_env_array(env_array, env_count);
	print_sorted_env(env_array, env_count);
	free(env_array);
}
//add by Reda
char **ft_fixexport(char **args)
{
    int i = 0;
    while (args[i] != NULL && args[i + 1] != NULL)
    {
        if ((unsigned char)args[i + 1][0] == 0x04)
        {
            char *new_arg = ft_strjoin(args[i], " ");
            char *combined = ft_strjoin(new_arg, ft_strchr(args[i + 1], 0x04) + 1);
            args[i] = combined;
            while (args[i + 1] != NULL)
            {
                args[i + 1] = args[i + 2];
                i++;
            }
        }
        else
        {
            i++;
        }
    }
    return args;
}
//

void	builtin_export(char **args, t_env **my_env)
{
	int		i;
	char	*str;

	if (!args[1])
	{
		print_sorted_environment(my_env);
	}
	else
	{
		i = 0;
		//add by Reda
		args = ft_fixexport(args);
		//
		while (args[++i] != NULL)
		{
			str = ft_strdup(args[i]);
			get_set_return(handle_export(str, my_env), 1);
			free(str);
		}
	}
}

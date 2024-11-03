/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:02:44 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/31 14:13:59 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// helper function delete it when no longer needed
// delete this
void	print_pwd_delet(void)
{
	char	cwd[PATH_MAX];

	getcwd(cwd, sizeof(cwd));
	printf(C"%s "RST, cwd);
}

// delete this
void	leak_report(void)
{
	system("echo hello from leak_report");
	system("leaks minishell");
}

int	get_set_return(int value, int flag_set_or_get)
{
	static int	return_value;

	if (flag_set_or_get == 1)
	{
		return_value = value;
		return (0);
	}
	else
		return (return_value);
}

// delete these
// atexit (leak_report);
//	 print_pwd_delet ();
//check_t_shell(the_shell); // delete this later
int	main(int argc, char **argv, char **env)
{
	t_shell	*the_shell;
	t_mem	*mm;
	char	*line;

	if (((void)argv, argc == 1))
	{
		int_in_main(&the_shell, &mm, env);
		while (1)
		{
			line = readline(GREEN "minishell$ " RST);
			if (!line)
				handle_null_in_main(the_shell);
			if (line[0] != '\0')
			{
				if (add_to_hitory_creat_token(&line, &the_shell) == -1)
					continue ;
				exec_clean_up_reset_signal(&the_shell);
			}
			free(line);
		}
		cleanup_at_exit(the_shell);
	}
	else
		ft_putendl_fd("Minishell: Minishell does not take args", 2);
	return (0);
}

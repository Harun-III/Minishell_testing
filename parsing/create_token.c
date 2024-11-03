/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:26:00 by rbouizer          #+#    #+#             */
/*   Updated: 2024/09/17 20:26:00 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	parse_tokens(char *line, t_mem **manager, t_token **tokens)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!handle_token(line, &i, tokens, manager))
			return (0);
	}
	if (!check_syntax_error(*tokens))
		return (0);
	return (1);
}

int	create_token(char *line, t_shell **the_shell)
{
	t_token	*tokens;

	tokens = NULL;
	if (!parse_tokens(line, &(*the_shell)->manager, &tokens))
	{
		ft_putendl_fd("minishell: Syntax error ", 2);
		if (g_received_signal == 0)
			get_set_return(258, SET_EXIT_STATUS);
		return (0);
	}
	if (!check_fd(tokens))
		return (0);
	if (!create_shell(tokens, the_shell))
		return (0);
	return (1);
}

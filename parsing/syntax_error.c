/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:07:53 by rbouizer          #+#    #+#             */
/*   Updated: 2024/09/22 17:07:53 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_not_word(t_type t)
{
	return (t == IN || t == OUT || t == PIPE || t == HERE || t == APPEND);
}

int	check_append(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_not_word(current->type))
		{
			if (!current->next || !current->next->data.origin
				|| is_not_word(current->next->type))
			{
				return (0);
			}
		}
		current = current->next;
	}
	return (1);
}

int	check_pipe(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		if ((i == 0 || i == ft_lstsize(tokens) - 1) && current->type == PIPE)
			return (0);
		current = current->next;
		i++;
	}
	return (1);
}

int	check_syntax_error(t_token *tokens)
{
	if (!check_append(tokens))
		return (0);
	if (!check_pipe(tokens))
		return (0);
	return (1);
}

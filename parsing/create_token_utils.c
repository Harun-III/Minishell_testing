/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:25:39 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/28 11:16:54 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fun0(char *str, int *i)
{
	while (str[*i] && is_space(str[*i]))
		(*i)++;
}

int	fun1(char *str, int *i, t_token **tokens, t_mem **manager)
{
	if (str[*i] == '\"')
	{
		if (!oxe1(str, i, tokens, manager))
			return (0);
	}
	else if (str[*i] == '\'')
	{
		if (!oxe2(str, i, tokens, manager))
			return (0);
	}
	return (1);
}

static int	fun3(char *str, int *i, t_token **tokens, t_mem **manager)
{
	char	*token;

	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		if (!ft_allocate(tokens, &token, "<<", HERE, manager))
			return (0);
		(*i)++;
	}
	else if (str[*i] == '<')
	{
		if (!ft_allocate(tokens, &token, "<", IN, manager))
			return (0);
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		if (!ft_allocate(tokens, &token, ">>", APPEND, manager))
			return (0);
		(*i)++;
	}
	else if (str[*i] == '>')
	{
		if (!ft_allocate(tokens, &token, ">", OUT, manager))
			return (0);
	}
	return ((*i)++, 1);
}

static int	fun4(char *line, int *i, t_token **tokens, t_mem **manager)
{
	int		start;
	char	*token;
	t_join	join_type;

	start = *i;
	join_type = NON_JOINBLE;
	while (line[*i] && !is_space(line[*i]) && line[*i] != '\"'
		&& line[*i] != '\'' && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
	{
		(*i)++;
	}
	token = ft_strndup_mm(manager, &line[start], *i - start);
	if (!token)
		return (0);
	if (line[*i] && !is_space(line[*i]) && line[*i] != '|'
		&& line[*i] != '<' && line[*i] != '>')
	{
		join_type = JOINBLE;
	}
	if (!add_token(tokens, join_type, DEFAULT, WORD, -1, token, manager))
		return (0);
	return (1);
}

int	handle_token(char *line, int *i, t_token **tokens, t_mem **manager)
{
	if (is_space(line[*i]))
		fun0(line, i);
	else if (line[*i] == '\"' || line[*i] == '\'')
	{
		if (!fun1(line, i, tokens, manager))
			return (0);
	}
	else if (line[*i] == '|')
	{
		if (!add_token(tokens, NON_JOINBLE, DEFAULT, PIPE,
				-1, ft_strdup_mm(manager, "|"), manager))
			return (0);
		(*i)++;
	}
	else if (line[*i] == '<' || line[*i] == '>')
	{
		if (!fun3(line, i, tokens, manager))
			return (0);
	}
	else
	{
		if (!fun4(line, i, tokens, manager))
			return (0);
	}
	return (1);
}

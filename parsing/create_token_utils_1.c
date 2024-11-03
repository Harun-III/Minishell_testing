/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 05:30:55 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/27 01:27:49 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\f' || c == '\v');
}

bool	is_type(int c)
{
	return (c == '<' || c == '>' || c == '|');
}

int	ft_allocate(t_token **tokens, char **token,	char *str, t_type type, t_mem **manager)
{
	*token = ft_strdup_mm(manager, str);
	if (!*token)
		return (0);
	if (!add_token(tokens, NON_JOINBLE, DEFAULT, type, -1, *token, manager))
		return (0);
	return (1);
}

int	oxe1(char *str, int *i, t_token **tokens, t_mem **manager)
{
	t_join	join_type;
	int		len;
	char	*dat;

	join_type = NON_JOINBLE;
	len = 0;
	(*i)++;
	while (str[*i + len] && str[*i + len] != '\"')
		len++;
	if (str[*i + len] != '\"')
		return (0);
	dat = ft_strndup_mm(manager, &str[*i], len);
	if (!dat)
		return (ft_putendl_fd("minishell: Failed to allocate memory", 2), 0);
	*i += len + 1;
	if (str[*i] != '\0' && !is_space(str[*i]) && !is_type(str[*i]))
		join_type = JOINBLE;
	if (!add_token(tokens, join_type, IN_DOUBLE, WORD, -1, dat, manager))
		return (0);
	return (1);
}

int	oxe2(char *str, int *i, t_token **tokens, t_mem **manager)
{
	t_join	join_type;
	int		len;
	char	*dat;

	join_type = NON_JOINBLE;
	len = 0;
	(*i)++;
	while (str[*i + len] && str[*i + len] != '\'')
		len++;
	if (str[*i + len] != '\'')
		return (0);
	dat = ft_strndup_mm(manager, &str[*i], len);
	if (!dat)
		return (ft_putendl_fd("minishell: Failed to allocate memory", 2), 0);
	*i += len + 1;
	if (str[*i] != '\0' && !is_space(str[*i]) && !is_type(str[*i]))
		join_type = JOINBLE;
	if (!add_token(tokens, join_type, IN_SINGALE, WORD, -1, dat, manager))
		return (0);
	return (1);
}

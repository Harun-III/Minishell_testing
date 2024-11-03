/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:09:50 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/19 18:00:11 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last_token = NULL;
	char		*token_start;

	if (str == NULL)
		str = last_token;
	if (str == NULL)
		return (NULL);
	while (*str && ft_strchr(delim, *str))
		str++;
	if (*str == '\0')
		return ((last_token = NULL, NULL));
	token_start = str;
	while (*str && !ft_strchr(delim, *str))
		str++;
	if (*str)
	{
		*str = '\0';
		last_token = str + 1;
	}
	else
		last_token = NULL;
	return (token_start);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 09:22:27 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/27 22:06:40 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static size_t	count_words(char const *s, char c)
{
	size_t	i;
	size_t	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static char	**set_mem(t_mem **manager, char **tab, char const *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			tab[i] = my_malloc(manager, sizeof(char) * (len + 1));
			if (!tab[i])
				return (NULL);
			ft_strlcpy(tab[i], s, len + 1);
			i++;
			s += len;
		}
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split_mm(t_mem **manager, char const *s, char c)
{
	size_t	count;
	char	**str;

	if (!s)
		return (NULL);
	count = count_words(s, c);
	str = my_malloc(manager, sizeof(char *) * (count + 1));
	if (str == NULL)
		return (NULL);
	str = set_mem(manager, str, s, c);
	return (str);
}

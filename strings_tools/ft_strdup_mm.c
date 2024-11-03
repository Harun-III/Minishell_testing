/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_mm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:09:31 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/27 22:11:45 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdup_mm(t_mem **manager, const char *s1)
{
	size_t	i;
	size_t	s_len;
	char	*copy;

	if (s1 == NULL)
		return (NULL);
	s_len = ft_strlen(s1);
	copy = (char *)my_malloc(manager, sizeof(char) * (s_len + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		copy[i] = s1[i];
		i++;
	}
	copy[s_len] = '\0';
	return (copy);
}

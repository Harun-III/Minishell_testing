/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_mm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:09:40 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/19 17:40:50 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup_mm(t_mem **manager, const char *s, size_t n)
{
	char	*new_str;

	new_str = my_malloc(manager, n + 1);
	if (!new_str)
		return (NULL);
	ft_strlcpy(new_str, s, n + 1);
	return (new_str);
}

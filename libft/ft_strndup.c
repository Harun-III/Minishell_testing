/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:07:59 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/27 15:10:37 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup ;
	size_t	len;
	
	if (s == NULL)
		return NULL;

	len = ft_strlen(s);
	if (len > n)
		len = n;

	dup = malloc(len + 1);
	if (dup == NULL)
		return NULL;

	ft_memcpy(dup, s, len);
	dup[len] = '\0';

	return dup;
}

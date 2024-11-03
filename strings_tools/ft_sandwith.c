/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sandwith.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:09:08 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/19 17:37:14 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_sandwitch_err(char *bread1, char *meat, char *bread2)
{
	ft_putstr_fd(bread1, 2);
	ft_putstr_fd(meat, 2);
	ft_putstr_fd(bread2, 2);
}

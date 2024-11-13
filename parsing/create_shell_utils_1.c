/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_shell_utils_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:20:21 by rbouizer          #+#    #+#             */
/*   Updated: 2024/11/10 14:28:32 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**fix_command(char **cmd)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strcmp(cmd[0], (char []){0x06, '\0'}) == 0 && cmd[1] == NULL)
		return (cmd);
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i], (char []){0x05, '\0'}) == 0)
			cmd[i] = "\0";
		if (ft_strcmp(cmd[i], (char []){0x06, '\0'}) != 0)
			cmd[j++] = cmd[i];
		i++;
	}
	cmd[j] = NULL;
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eghalime <eghalime@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:36:15 by eghalime          #+#    #+#             */
/*   Updated: 2024/10/30 18:36:36 by eghalime         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_case_1(t_cmd *cmd)
{
	if (setup_redirections(cmd->redir) != 0)
		exit(EXIT_CANNOT_EXECUTE);
	exit(0);
}

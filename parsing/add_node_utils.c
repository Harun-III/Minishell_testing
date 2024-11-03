/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:47:23 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/08 15:24:11 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cr_shell(t_shell **shells, t_cmd *cmd_list)
{
	if (shells && *shells)
	{
		get_set_return(0, 1);
		(*shells)->cmd_list = cmd_list;
		return (1);
	}
	return (0);
}

t_redir	*cr_redir(int fd, const char *file, t_type type, t_mem **manager)
{
	t_redir	*redir;

	redir = (t_redir *)my_malloc(manager, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->fd = fd;
	redir->file = ft_strdup_mm(manager, file);
	redir->type = type;
	redir->next = NULL;
	return (redir);
}

void	add_back_redir(t_redir **head, t_redir *new_redir)
{
	t_redir	*current;

	if (!head || !new_redir)
		return ;
	if (*head == NULL)
		*head = new_redir;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_redir;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 20:29:41 by rbouizer          #+#    #+#             */
/*   Updated: 2024/09/21 20:29:41 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	add_token(t_token **tokens, t_join join, t_state state, t_type type, int fd, char *origin, t_mem **manager)
{
	t_token	*new_token;
	t_token	*current;

	new_token = (t_token *)my_malloc(manager, sizeof(t_token));
	if (!new_token)
		return (0);
	new_token->join = join;
	new_token->state = state;
	new_token->type = type;
	new_token->data.fd = fd;
	new_token->data.origin = origin;
	new_token->data.content = origin;
	new_token->data.type_fd = -1;
	new_token->next = NULL;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
	return (1);
}

void	add_back_token(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (*tokens == NULL)
		*tokens = new_token;
	else
	{
		current = *tokens;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

t_cmd	*cr_cmd( bool type, const char *cmd, char **args, t_redir *redir, t_mem **manager)
{
	t_cmd	*command;

	command = (t_cmd *)my_malloc(manager, sizeof(t_cmd));
	if (!command || ft_strcmp(cmd, (char []){0x06, '\0'}) == 0)
		return (NULL);
	command->type = type;
	command->cmd = ft_strdup_mm(manager, cmd);
	command->args = args;
	command->redir = redir;
	command->next = NULL;
	return (command);
}

void	add_back_cmd(t_cmd **head, t_cmd *new_cmd)
{
	t_cmd	*current;

	if (!head || !new_cmd)
		return ;
	if (*head == NULL)
		*head = new_cmd;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_cmd;
	}
}

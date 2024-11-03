/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:59:15 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/28 11:40:42 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// #include <stddef.h>

// void print_token(t_token *token)
// {
// 	printf("Join: ");
// 	if (token->join == JOINBLE)
// 		printf("JOINBLE , ");
// 	else
// 		printf("NON_JOINBLE , ");

// 	printf("State: ");
// 	switch (token->state) {
// 		case DEFAULT:
// 			printf("DEFAULT , ");
// 			break;
// 		case IN_SINGALE:
// 			printf("IN_SINGALE , ");
// 			break;
// 		case IN_DOUBLE:
// 			printf("IN_DOUBLE , ");
// 			break;
// 		case DOLLAR:
// 			printf("DOLLAR , ");
// 			break;
// 	}
// 	printf("Type: ");
// 	switch (token->type) {
// 		case IN:
// 			printf("IN , ");
// 			break;
// 		case OUT:
// 			printf("OUT , ");
// 			break;
// 		case HERE:
// 			printf("HERE , ");
// 			break;
// 		case APPEND:
// 			printf("APPEND , ");
// 			break;
// 		case ERROR:
// 			printf("ERROR , ");
// 			break;
// 		case WORD:
// 			printf("WORD , ");
// 			break;
// 		case PIPE:
// 			printf("PIPE , ");
// 			break;
// 	}
// 	printf("fd : %d , ", token->data.fd);
// 	if (token->data.type_fd == IN || token->data.type_fd == OUT
// 		|| token->data.type_fd == HERE
// 		|| token->data.type_fd == APPEND || token->data.type_fd == ERROR
// 		|| token->data.type_fd == WORD || token->data.type_fd == PIPE)
// 		{
// 		printf("Type FD: ");
// 		switch (token->data.type_fd)
// 		{
// 			case IN:
// 				printf("IN , ");
// 				break;
// 			case OUT:
// 				printf("OUT , ");
// 				break;
// 			case HERE:
// 				printf("HERE , ");
// 				break;
// 			case APPEND:
// 				printf("APPEND , ");
// 				break;
// 			case ERROR:
// 				printf("ERROR , ");
// 				break;
// 			case WORD:
// 				printf("WORD , ");
// 				break;
// 			case PIPE:
// 				printf("PIPE , ");
// 				break;
// 		}
// 	} else
// 		printf("Invalid Type FD: %d\n", token->data.type_fd);
// 	printf("Origin: %s \n", token->data.origin);
// }

// void	print_all_tokens(t_token *head)
// {
// 	t_token	*current;

// 	current = head;
// 	while (current != NULL)
// 	{
// 		print_token(current);
// 		current = current->next;
// 		printf("-------------------------------\n");
// 	}
// }

// void	print_redir(t_redir *redir)
// {
// 	while (redir)
// 	{
// 		printf("  Redirection:\n");
// 		printf("    File: %s\n", redir->file);
// 		printf("    File Descriptor: %d\n", redir->fd);
// 		printf("    Type: %d\n", redir->type);
// 		redir = redir->next;
// 	}
// }

// void	print_cmd(t_cmd *cmd)
// {
// 	while (cmd)
// 	{
// 		printf("Command:\n");
// 		printf("  Type: %s\n", cmd->type ? "Built-in" : "External");
// 		printf("  Command: %s\n", cmd->cmd);
// 		if (cmd->args)
// 		{
// 			printf("  Arguments:\n");
// 			for (int i = 0; cmd->args[i] != NULL; i++)
// 				printf("    Arg[%d]: %s\n", i, cmd->args[i]);
// 		}
// 		else
// 			printf("  No arguments.\n");
// 		if (cmd->redir)
// 			print_redir(cmd->redir);
// 		else
// 			printf("  No redirections.\n");
// 		cmd = cmd->next; 
// 		printf("-------------------------------\n");
// 	}
// }

// size_t count_tokens(t_token *head)
// {
//     size_t count = 0;
//     t_token *current = head;

//     while (current != NULL)
//     {
//         count++;
//         current = current->next;
//     }

//     return count;
// }

// size_t count_char_array(char **array)
// {
//     size_t count = 0;

//     if (array == NULL)
//         return 0;

//     while (array[count] != NULL)
//     {
//         count++;
//     }

//     return count;
// }

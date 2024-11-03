/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_managment.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouizer <rbouizer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:03:36 by rbouizer          #+#    #+#             */
/*   Updated: 2024/10/27 15:13:25 by rbouizer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    *my_malloc(t_mem** manager, size_t size)
{
	void*   ptr;
	t_mem*  new_node;

	ptr = malloc(size);
	if (ptr == NULL)
	{
		ft_putendl_fd("Error: Memory allocation failed",2);
		return NULL;
	}
	new_node = (t_mem*)malloc(sizeof(t_mem));
	if (new_node == NULL)
	{
		ft_putendl_fd("Error: Memory allocation for manager failed",2);
		free(ptr);
		return NULL;
	}
	new_node->ptr = ptr;
	new_node->next = *manager;
	*manager = new_node;
	return ptr;
}

void    my_free(t_mem** manager, void* ptr)
{
	t_mem* current;
	t_mem* previous;

	current = *manager;
	previous = NULL;
	while (current != NULL)
	{
		if (current->ptr == ptr)
		{
			free(ptr);
			if (previous == NULL)
				*manager = current->next;
			else
				previous->next = current->next;
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
	ft_putendl_fd("Error: Attempt to free untracked memory", 2);
}

void    cleanup(t_mem** manager)
{
	t_mem*  current;
	t_mem*  next;

	current = *manager;
	while (current != NULL) 
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*manager = NULL;
}

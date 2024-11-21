/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:03:02 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/21 13:01:41 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "get_next_line.h"

//foncction pour trouver un fd dans la liste chainée
t_fd_buffer *gnl_find_fd(t_fd_buffer *head, int fd)
{
	while (head)
	{
		if(head->fd == fd)
			return (head);
		head = head->next;
	}
	return (NULL);
}

t_fd_buffer	*gnl_add_fd(t_fd_buffer **head, int fd)
{
	t_fd_buffer	*new_node;
	
	if (fd > sysconf(_SC_OPEN_MAX))
		return (NULL);
	new_node = (t_fd_buffer *)malloc(sizeof(t_fd_buffer));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->buffer = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

void	gnl_remove_fd(t_fd_buffer **head, int fd)
{
	t_fd_buffer	*current;
	t_fd_buffer	*prev;

	current = *head;
	prev = NULL;

	while (current)
	{
		if (current->fd == fd)
		{
			if(prev)
				prev->next = current->next;
			else
				*head = current->next;
			free(current->buffer);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
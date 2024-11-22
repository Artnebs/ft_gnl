/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:03:02 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/22 17:47:11 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_buffer	*gnl_find_or_add_fd(int fd, t_fd_buffer **head)
{
	t_fd_buffer	*current;
	t_fd_buffer	*new_node;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
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
			if (prev)
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

size_t	gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*gnl_strjoin_and_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;
	size_t	i;

	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	result = malloc(len_s1 + len_s2 + 1);
	if (!result)
		return (free(s1), NULL);
	i = 0;
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i - len_s1 < len_s2)
	{
		result[i] = s2[i - len_s1];
		i++;
	}
	return (result[i] = '\0', free(s1), result);
}

int	gnl_find_newline(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

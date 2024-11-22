/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:03:02 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/21 16:41:44 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_buffer	*gnl_find_fd(t_fd_buffer *head, int fd)
{
	while (head)
	{
		if (head->fd == fd)
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

char	*gnl_strjoin_and_free(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;
	size_t	i;

	len_s1 = 0;
	while (s1 && s1[len_s1])
		len_s1++;
	len_s2 = 0;
	while (s2 && s2[len_s2])
		len_s2++;
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

char	*gnl_extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		line_length;
	int		i;

	if (!buffer || !*buffer || **buffer == '\0')
		return (NULL);
	line_length = gnl_find_newline(*buffer);
	if (line_length >= 0)
		line_length += 1;
	else
	{
		line_length = 0;
		while ((*buffer)[line_length])
			line_length++;
	}
	line = malloc(line_length + 1);
	if (!line)
		return (free(*buffer), *buffer = NULL, NULL);
	i = 0;
	while (i < line_length)
	{
		line[i] = (*buffer)[i];
		i++;
	}
	line[i] = '\0';
	temp = NULL;
	if ((*buffer)[line_length])
	{
		i = 0;
		while ((*buffer)[line_length + i])
			i++;
		temp = malloc(i + 1);
		if (!temp)
			return (free(line), free(*buffer), *buffer = NULL, NULL);
		i = 0;
		while ((*buffer)[line_length + i])
		{
			temp[i] = (*buffer)[line_length + i];
			i++;
		}
		temp[i] = '\0';
	}
	free(*buffer);
	*buffer = temp;
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:59 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/21 16:45:26 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include "get_next_line_bonus.h"

static char	*read_to_buffer(int fd, t_fd_buffer *current_fd,
							t_fd_buffer **fd_list)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	while ((bytes_read = read(fd, temp_buffer, BUFFER_SIZE)) > 0)
	{
		temp_buffer[bytes_read] = '\0';
		current_fd->buffer = gnl_strjoin_and_free(current_fd->buffer, temp_buffer);
		if (!current_fd->buffer)
		{
			free(temp_buffer);
			gnl_remove_fd(fd_list, fd);
			return (NULL);
		}
		if (gnl_find_newline(current_fd->buffer) >= 0)
			break ;
	}
	free(temp_buffer);
	if (bytes_read < 0)
		return (gnl_remove_fd(fd_list, fd), NULL);
	return (current_fd->buffer);
}

int	gnl_find_newline(char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static t_fd_buffer	*fd_list = NULL;
	t_fd_buffer			*current_fd;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FD_SETSIZE)
		return (NULL);
	current_fd = gnl_find_fd(fd_list, fd);
	if (!current_fd)
		current_fd = gnl_add_fd(&fd_list, fd);
	if (!current_fd)
		return (NULL);
	if (!read_to_buffer(fd, current_fd, &fd_list))
	{
		gnl_remove_fd(&fd_list, fd);
		return (NULL);
	}
	line = gnl_extract_line(&(current_fd->buffer));
	if (!line && (!current_fd->buffer || *current_fd->buffer == '\0'))
		gnl_remove_fd(&fd_list, fd);
	return (line);
}


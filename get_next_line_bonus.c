/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:59 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/24 13:01:53 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static t_fd_buffer	*fd_list = NULL;
	t_fd_buffer			*current_fd;
	char				*line;

	current_fd = gnl_find_or_add_fd(fd, &fd_list);
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

char	*read_to_buffer(int fd, t_fd_buffer *current_fd, t_fd_buffer **fd_list)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = malloc(BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buffer[bytes_read] = '\0';
		current_fd->buffer = gnl_strjoin_and_free(current_fd->buffer,
				temp_buffer);
		if (!current_fd->buffer)
			return (free(temp_buffer), gnl_remove_fd(fd_list, fd), NULL);
		if (gnl_find_newline(current_fd->buffer) >= 0)
			break ;
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	free(temp_buffer);
	if (bytes_read < 0)
		return (gnl_remove_fd(fd_list, fd), NULL);
	return (current_fd->buffer);
}

char	*gnl_extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		line_length;

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
	line = gnl_allocate_line(*buffer, line_length);
	if (!line)
		return (free(*buffer), *buffer = NULL, NULL);
	temp = gnl_update_buffer(*buffer, line_length);
	return (free(*buffer), *buffer = temp, line);
}

char	*gnl_update_buffer(char *buffer, int line_length)
{
	char	*temp;
	int		i;

	i = 0;
	while (buffer[line_length + i])
		i++;
	temp = malloc(i + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (buffer[line_length + i])
	{
		temp[i] = buffer[line_length + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*gnl_allocate_line(char *buffer, int line_length)
{
	char	*line;
	int		i;

	i = 0;
	line = malloc(line_length + 1);
	if (!line)
		return (NULL);
	while (i < line_length)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

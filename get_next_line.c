/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:08 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/22 18:09:06 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_and_return_null(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
	return (NULL);
}

static char	*read_and_append(int fd, char **buffer)
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
		*buffer = gnl_strjoin(*buffer, temp_buffer);
		if (!*buffer)
			return (free(temp_buffer), NULL);
		if (gnl_find_newline(*buffer) >= 0)
			break ;
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	free(temp_buffer);
	if (bytes_read < 0)
		return (free_and_return_null(buffer));
	return (*buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_and_append(fd, &buffer);
	if (!buffer || *buffer == '\0')
		return (free_and_return_null(&buffer));
	line = gnl_extract_line(&buffer);
	if (!line && (!buffer || *buffer == '\0'))
		free_and_return_null(&buffer);
	return (line);
}

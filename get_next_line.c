/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:08 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/20 19:39:13 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char	temp_buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 )
		return (NULL);
	while ((bytes_read = read(fd, temp_buffer, BUFFER_SIZE)) > 0)
	{
		temp_buffer[bytes_read] = '\0';
		buffer = gnl_strjoin(buffer, temp_buffer);
		if (gnl_find_newline(buffer) >= 0)
			break ;
	}
	if (bytes_read < 0 || (bytes_read == 0 && (!buffer || *buffer == '\0')))
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	return (gnl_extract_line(&buffer));
}


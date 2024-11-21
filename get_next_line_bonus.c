/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:59 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/21 14:45:39 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_fd_buffer	*fd_list = NULL;
	t_fd_buffer	*current_fd;
	char	*temp_buffer;
	ssize_t	bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= sysconf(_SC_OPEN_MAX))
		return (NULL);
	current_fd = gnl_find_fd(fd_list, fd);
	if (!current_fd)
		current_fd = gnl_add_fd(&fd_list, fd);
	if (!current_fd)
			return (NULL);
	temp_buffer = malloc(BUFFER_SIZE + 1);
	while ((bytes_read = read(fd, temp_buffer, BUFFER_SIZE)) > 0)
	{
		temp_buffer[bytes_read] = '\0';
		current_fd->buffer = gnl_strjoin(current_fd->buffer, temp_buffer);
		if (!current_fd->buffer)
			return (free(temp_buffer), gnl_remove_fd(&fd_list, fd), NULL);
		if (gnl_find_newline(current_fd->buffer) >= 0)
			break ;
	}
	free(temp_buffer);
	if(bytes_read < 0 || (bytes_read == 0 && (!current_fd->buffer || *current_fd->buffer == '\0')))
		return (gnl_remove_fd(&fd_list, fd), NULL);
	return (gnl_extract_line(&(current_fd->buffer)));
}

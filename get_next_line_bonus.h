/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:12 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/26 12:19:19 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# define MAX_FD 1024

/* ************************************************************************** */
/* BUFFER DEFINITION */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************** */
/* INCLUDES */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "get_next_line.h"

/* ************************************************************************** */
/* STRUCTURES */
/* ************************************************************************** */

typedef struct s_fd_buffer
{
	int					fd;
	char				*buffer;
	struct s_fd_buffer	*next;
}	t_fd_buffer;

/* ************************************************************************** */
/* PROTOTYPES */
/* ************************************************************************** */

// Main function for getting the next line
char		*get_next_line(int fd);

// Utility functions for get_next_line
void		gnl_remove_fd(t_fd_buffer **head, int fd);
size_t		gnl_strlen(const char *str);
char		*gnl_strjoin_and_free(char *s1, char *s2);
int			gnl_find_newline(const char *str);
char		*get_next_line(int fd);
char		*read_to_buffer(int fd, t_fd_buffer *current_fd,
				t_fd_buffer **fd_list);
char		*gnl_extract_line(char **buffer);
char		*gnl_update_buffer(char *buffer, int line_length);
char		*gnl_allocate_line(char *buffer, int line_length);
t_fd_buffer	*gnl_find_or_add_fd(int fd, t_fd_buffer **head);

#endif

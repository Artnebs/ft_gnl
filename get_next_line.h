/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:12 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/19 19:34:21 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

/* ************************************************************************** */
/* INCLUDES */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>

/* ************************************************************************** */
/* STRUCTURES */
/* ************************************************************************** */
typedef struct s_fd_buffer
{
	int	fd;
	char	*buffer;
}	t_fd_buffer;


/* ************************************************************************** */
/* PROTOTYPES */
/* ************************************************************************** */

char	*get_next_line(int fd);
char	*gnl_extract_line(char **buffer);

int	gnl_find_newline(char *s);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char *s, size_t start, size_t len);
size_t	gnl_strlen(const char *s);

/* ************************************************************************** */
/* BONUS (Pour une éventuelle extension) */
/* ************************************************************************** */



/* ************************************************************************** */
/* DEBUG */
/* ************************************************************************** */




#endif
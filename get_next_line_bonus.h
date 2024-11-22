/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:12 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/21 16:15:05 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
# include <sys/types.h>
# include "get_next_line.h"

/* ************************************************************************** */
/* STRUCTURES */
/* ************************************************************************** */

typedef struct s_fd_buffer
{
	int	fd;
	char	*buffer;
	struct s_fd_buffer	*next;
}	t_fd_buffer;

/* ************************************************************************** */
/* PROTOTYPES */
/* ************************************************************************** */

// Fonction principale
char	*get_next_line(int fd);

// Fonctions utilitaires pour get_next_line
t_fd_buffer	*gnl_find_fd(t_fd_buffer *head, int fd);
t_fd_buffer	*gnl_add_fd(t_fd_buffer **head, int fd);
void		gnl_remove_fd(t_fd_buffer **head, int fd);
char		*gnl_strjoin_and_free(char *s1, char *s2);
char		*gnl_extract_line(char **buffer);

#endif

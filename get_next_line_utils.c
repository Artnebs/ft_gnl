/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:04 by anebbou           #+#    #+#             */
/*   Updated: 2024/11/20 17:45:54 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//fonction pour trouver un \n dans une chaine de caractères
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

//fonction pour faire une chaines de caractères avec 2 sous chaines - free after
char *gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	len_s1 = gnl_strlen(s1);
	len_s2 = gnl_strlen(s2);
	result = (char *)malloc(len_s1 + len_s2	+ 1);
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		result[i] = s1[i];
	j = 0;
	while (j < len_s2)
		result[i++] = s2[j++];
	result[i] = '\0';
	free(s1);
	return (result);
}

//fonction pour extraire une chaine de caractères jusqu'a \n
char *gnl_substr(char *s, size_t start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s || start >= gnl_strlen(s))
		return (NULL);
	if (len > gnl_strlen(s) - start)
		len = gnl_strlen(s) - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

//fonction pour calculer taille d'une chaine de caractères
size_t	gnl_strlen(const char *s)
{
	ssize_t len; 

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}
//fonction pour extraire une ligne de la chaine de caractères et la supprimer de la chaine
char	*gnl_extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	size_t	line_length;
	size_t	buffer_length;
	
	if (!buffer || !*buffer || **buffer == '\0')
		return (NULL);
	line_length = gnl_find_newline(*buffer) + 1;
	if (line_length == 0)
		line_length = gnl_strlen(*buffer);
	line = gnl_substr(*buffer, 0, line_length);
	buffer_length = gnl_strlen(*buffer);
	if (line_length < buffer_length)
		temp = gnl_substr(*buffer, line_length, buffer_length - line_length);
	else
		temp = NULL;
	free(*buffer);
	*buffer = temp;
	return (line);
}

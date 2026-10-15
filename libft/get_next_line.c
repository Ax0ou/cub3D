/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalvard <aalvarad@student.42lausanne.ch    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by alvrd             #+#    #+#             */
/*   Updated: 2026/05/20 13:28:26 by aalvard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash);
static char	*extract_line(char *stash);
static char	*keep_rest(char *stash);

static char	*read_to_stash(int fd, char *stash)
{
	ssize_t	bytes;
	char	buffer[BUFFER_SIZE + 1];
	char	*tmp;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	while (!ft_strchr(stash, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(stash), NULL);
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		tmp = ft_strjoin(stash, buffer);
		if (!tmp)
			return (free(stash), NULL);
		free(stash);
		stash = tmp;
	}
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*newline;
	size_t	len;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (newline)
		len = (newline - stash) + 1;
	else
		len = ft_strlen(stash);
	line = ft_substr(stash, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

static char	*keep_rest(char *stash)
{
	char	*newline;
	char	*rest;
	size_t	start;

	if (!stash || stash[0] == '\0')
		return (NULL);
	newline = ft_strchr(stash, '\n');
	if (!newline)
		return (free(stash), NULL);
	start = (newline - stash) + 1;
	rest = ft_substr(stash, start, ft_strlen(stash) - start);
	if (!rest)
		return (free(stash), NULL);
	free(stash);
	if (rest[0] == '\0')
		return (free(rest), NULL);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = keep_rest(stash);
	return (line);
}

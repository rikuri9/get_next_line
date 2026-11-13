/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riwamoto <riwamoto@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 16:30:18 by riwamoto          #+#    #+#             */
/*   Updated: 2026/11/13 19:24:50 by riwamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash)
{
	char	*buf;
	char	*tmp;
	ssize_t	bytes_read;

	if (has_newline(stash))
		return (stash);
	buf = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buf)
		return (free(stash), NULL);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = join_chunk(tmp, buf);
		free(tmp);
		if (!stash || has_newline(buf))
			break ;
	}
	free(buf);
	if (bytes_read < 0)
		return (free(stash), NULL);
	return (stash);
}

static char	*extract_line(const char *stash)
{
	char	*line;
	size_t	len;
	size_t	i;

	if (!stash || !*stash)
		return (NULL);
	len = line_len(stash);
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*trim_stash(char *stash)
{
	char	*rest;
	size_t	start;
	size_t	i;

	start = line_len(stash);
	if (!stash[start])
	{
		free(stash);
		return (NULL);
	}
	rest = malloc(sizeof(char) * (ft_strlen(stash + start) + 1));
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	i = 0;
	while (stash[start + i])
	{
		rest[i] = stash[start + i];
		i++;
	}
	rest[i] = '\0';
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = trim_stash(stash);
	return (line);
}

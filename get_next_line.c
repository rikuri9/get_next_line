/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riwamoto <riwamoto@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 16:37:14 by riwamoto          #+#    #+#             */
/*   Updated: 2026/11/11 18:43:03 by riwamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_to_stash(int fd, char *stash, int *flag)
{
	char	*save;
	ssize_t	bytes_read;
	char	*tmp;

	save = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!save)
	{
		free(stash);
		return (NULL);
	}
	while (*flag == -1)
	{
		bytes_read = read(fd, save, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		save[bytes_read] = '\0';
		tmp = stash;
		stash = join_line(tmp, save, flag);
		free(tmp);
	}
	free(save);
	return (stash);
}

static char	*extract_line(char	**stash, int flag)
{
	char	*line;
	char	*tmp;

	if (flag == -1)
	{
		if (!*stash || !**stash)
		{
			free(*stash);
			*stash = NULL;
			return (NULL);
		}
		line = *stash;
		*stash = NULL;
		return (line);
	}
	tmp = *stash;
	line = get_line(tmp, flag + 1);
	*stash = join_line(tmp + flag + 1, "", NULL);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			line_break_flag;

	line_break_flag = find_line_break(stash);
	if (line_break_flag == -1)
		stash = read_to_stash(fd, stash, &line_break_flag);
	return (extract_line(&stash, line_break_flag));
}

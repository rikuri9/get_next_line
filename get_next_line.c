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

static int	check_line_break(const char c)
{
	return (c == '\n');
}

static size_t	get_bytes(const char *s)
{
	size_t	bytes;

	if (!s)
		return (0);
	bytes = 0;
	while (s[bytes])
		bytes++;
	return (bytes);
}

static void	*join_line(char *s1, char *s2, int *flag)
{
	char	*line;
	size_t	s1_bytes;
	size_t	s2_bytes;
	size_t	i;

	if (!s2)
		return (NULL);
	s1_bytes = get_bytes(s1);
	s2_bytes = get_bytes(s2);
	line = malloc(sizeof(char) * (s1_bytes + s2_bytes + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < s1_bytes + s2_bytes)
	{
		if (i < s1_bytes)
			line[i] = s1[i];
		else
			line[i] = s2[i - s1_bytes];
		if (flag && *flag == -1 && check_line_break(line[i]))
			*flag = i;
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_line(char *s, int len)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_line[i] = s[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*get_next_line(int fd)
{
	char		save[BUFFER_SIZE + 1];
	static char	*stash;
	int			line_break_flag;
	char		*line;
	ssize_t		bytes_read;
	char		*tmp;
	int			i;

	line_break_flag = -1;
	i = 0;
	while (stash && stash[i] && line_break_flag == -1)
	{
		if (check_line_break(stash[i]))
			line_break_flag = i;
		i++;
	}
	while (line_break_flag == -1)
	{
		bytes_read = read(fd, save, BUFFER_SIZE);
		if (bytes_read <= 0)
			break ;
		save[bytes_read] = '\0';
		tmp = stash;
		stash = join_line(tmp, save, &line_break_flag);
		free(tmp);
	}
	if (line_break_flag == -1)
	{
		if (!stash || !*stash)
		{
			free(stash);
			stash = NULL;
			return (NULL);
		}
		line = stash;
		stash = NULL;
		return (line);
	}
	tmp = stash;
	line = get_line(tmp, line_break_flag + 1);
	stash = join_line(tmp + line_break_flag + 1, "", NULL);
	free(tmp);
	return (line);
}

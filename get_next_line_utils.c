/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riwamoto <riwamoto@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 17:00:05 by riwamoto          #+#    #+#             */
/*   Updated: 2026/11/11 15:59:05 by riwamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_line_break(const char c)
{
	return (c == '\n');
}

size_t	get_bytes(const char *s)
{
	size_t	bytes;

	if (!s)
		return (0);
	bytes = 0;
	while (s[bytes])
		bytes++;
	return (bytes);
}

void	*join_line(char *s1, char *s2, int *flag)
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

char	*get_line(char *s, int len)
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

int	find_line_break(char *s)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (check_line_break(s[i]))
			return (i);
		i++;
	}
	return (-1);
}

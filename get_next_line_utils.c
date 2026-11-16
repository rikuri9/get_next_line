/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riwamoto <riwamoto@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 16:31:00 by riwamoto          #+#    #+#             */
/*   Updated: 2026/11/16 14:32:18 by riwamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	has_newline(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*join_chunk(const char *stash, char *buf)
{
	char	*joined;
	size_t	stash_len;
	size_t	buf_len;
	size_t	i;

	stash_len = 0;
	if (stash)
		stash_len = ft_strlen(stash);
	buf_len = ft_strlen(buf);
	joined = malloc(sizeof(char) * (stash_len + buf_len + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (i < stash_len + buf_len)
	{
		if (i < stash_len)
			joined[i] = stash[i];
		else
			joined[i] = buf[i - stash_len];
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

size_t	line_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != '\n')
		len++;
	if (s[len] == '\n')
		len++;
	return (len);
}

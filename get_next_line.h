/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: riwamoto <riwamoto@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 17:00:08 by riwamoto          #+#    #+#             */
/*   Updated: 2026/11/11 18:46:29 by riwamoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
int		check_line_break(const char c);
size_t	get_bytes(const char *s);
void	*join_line(char *s1, char *s2, int *flag);
char	*get_line(char *s, int len);
int		find_line_break(char *s);

#endif
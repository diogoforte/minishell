/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 11:46:27 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/27 11:46:27 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != 10)
		i++;
	if (str[i] == 10)
		i++;
	return (i);
}

int	nl(char *buf)
{
	int	i;
	int	g;
	int	j;

	i = 0;
	g = 0;
	j = 0;
	while (buf[i])
	{
		if (j == 1)
			buf[g++] = buf[i];
		if (buf[i] == 10)
			j = 1;
		buf[i++] = 0;
	}
	return (j);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE + 1];
	int			i;

	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1)
	{
		while (buf[i])
			buf[i++] = 0;
		return (NULL);
	}
	line = NULL;
	while (*buf || read(fd, buf, BUFFER_SIZE) > 0)
	{
		line = ft_strjoin(line, buf);
		if (nl(buf) == 1)
			break ;
	}
	return (line);
}

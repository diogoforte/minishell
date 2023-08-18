/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:54:22 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 20:29:46 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*insert_space(char *line)
{
	char	*new_line;
	char	*tmp;

	new_line = malloc(strlen(line) + ft_strlen(line) + 1);
	tmp = new_line;
	while (*line)
	{
		if (line == tmp && (*line == '>' || *line == '<'))
		{
			*tmp++ = ' ';
			*tmp++ = *line++;
			continue ;
		}
		if ((*line == '>' || *line == '<') && *(line - 1) != ' ' && *(line
				- 1) != *(line))
			*tmp++ = ' ';
		*tmp++ = *line++;
	}
	*tmp = '\0';
	return (new_line);
}

char	*remove_char(char *str, char *clean, char c)
{
	size_t	i;

	i = ft_strlen(clean);
	while (*str == c)
		str++;
	while (*str && *str != c)
	{
		clean[i++] = *str;
		str++;
	}
	while (*str == c)
		str++;
	return (str);
}

char	*skip_spaces(char *start)
{
	while (*start && *start == ' ')
		start++;
	return (start);
}

char	*preprocess_line(char *line)
{
	if ((ft_strchr(line, '>') || ft_strchr(line, '<')) && !ft_strchr(line, ' '))
		return (insert_space(line));
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:54:22 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 02:24:51 by bcastelo         ###   ########.fr       */
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

char	*remove_char(char *str, char c)
{
	char	*new;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
		if (str[i++] == c)
			j++;
	new = ft_calloc(ft_strlen(str) - j + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
			new[j++] = str[i];
		i++;
	}	
	return (new);
}

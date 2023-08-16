/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 23:54:22 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 23:59:51 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*insert_space(char *line)
{
	char	*new_line;
	char	*tmp;

	new_line = malloc(strlen(line) + 2);
	tmp = new_line;
	while (*line)
	{
		if (*line == '>' && *(line - 1) != ' ')
			*tmp++ = ' ';
		*tmp++ = *line++;
	}
	*tmp = '\0';
	return (new_line);
}

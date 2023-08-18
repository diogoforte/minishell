/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 22:50:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 22:54:14 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_syntax_errors(char **commands)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (commands[i])
	{
		j = 0;
		check = 0;
		while (commands[i][j])
		{
			if (!ft_isspace(commands[i][j++]))
				check = 1;
		}
		if (!check)
		{
			printf("syntax error near unexpected token `|'\n");
			ft_freematrix(commands);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**get_pipes(char *line)
{
	char	**commands;

	if (line[0] == '|' || line[ft_strlen(line) - 1] == '|')
	{
		printf("syntax error near unexpected token `|'\n");
		return (NULL);
	}
	commands = split_pipes(line, '|');
	if (!commands)
		return (NULL);
	if (!check_syntax_errors(commands))
		return (NULL);
	return (commands);
}

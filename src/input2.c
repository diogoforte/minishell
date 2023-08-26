/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:09:16 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/26 23:10:02 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	validate_pipes_2(char *line, int i)
{
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|')
		{
			if (i == 0)
				return (0);
			if (!line[i + 1] || line[i + 1] == '|')
				return (0);
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '|')
				return (0);
		}
		else
			while (line[i] && line[i] != '|' && line[i] != ' ')
				i++;
	}
	return (1);
}

int	validate_red_2(char *line, int i)
{
	char	current_redirection;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] != '>' && line[i] != '<')
			i++;
		if (line[i] == '>' || line[i] == '<')
		{
			current_redirection = line[i];
			if (i != 0 && line[i - 1] != ' ' && line[i
					- 1] != current_redirection && line[i - 1] != '|')
				return (0);
			if (line[i + 1] == current_redirection)
				i++;
			i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (line[i] == '>' || line[i] == '<' || !line[i])
				return (0);
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:09:16 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/28 17:49:10 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	validate_pipes_2(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] == '|')
		{
			if (i == 0)
				return (0);
			if (!line[i + 1] || line[i + 1] == '|' || line[i + 1] == '>'
				|| line[i + 1] == '<')
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
	return (validate_pipes_3(line));
}

int	validate_red_2(char *line)
{
	int		i;
	char	current_redirection;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<')
		{
			current_redirection = line[i];
			i++;
			if (line[i] == current_redirection)
				i++;
			while (line[i] && line[i] == ' ')
				i++;
			if (!line[i] || line[i] == '>' || line[i] == '<' || line[i] == '|')
				return (0);
		}
		else
			i++;
	}
	return (1);
}

int	only_spaces(char *line)
{
	while (*line)
	{
		if (!ft_isspace(*line))
			return (0);
		line++;
	}
	return (1);
}

char	*ignore_in_quotes(char *line)
{
	char		*clean;
	int			i;
	t_in_quote	state;

	clean = ft_strdup(line);
	init_quote_state(&state);
	i = 0;
	while (clean[i])
	{
		swap_quote_state(&state, clean[i]);
		if (state.inside)
			clean[i] = 'a';
		i++;
	}
	return (clean);
}

int	validate_pipes_3(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (i >= 0 && line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (0);
	return (1);
}

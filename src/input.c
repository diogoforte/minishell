/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 05:06:45 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/27 00:35:55 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_line(char **envp)
{
	char	*line;

	line = NULL;
	line = readline("minishell$> ");
	if (!line)
	{
		ft_freematrix(envp);
		rl_clear_history();
		exit(0);
	}
	return (line);
}

int	check_input(char *line)
{
	int	status;

	if (!*line)
	{
		free(line);
		return (0);
	}
	status = 2;
	if (!validate_redirections(line) || !validate_pipes(line))
	{
		ft_dprintf(2, "minishell: syntax error\n");
		free(line);
		exit_status(&status);
		return (0);
	}
	return (1);
}

int	validate_redirections(char *line)
{
	int			i;
	t_in_quote	state;

	init_quote_state(&state);
	i = 0;
	while (line[i])
	{
		swap_quote_state(&state, line[i]);
		if ((line[i] == '>' || line[i] == '<') && !state.inside)
		{
			if (!validate_red_2(line, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	validate_pipes(char *line)
{
	int			i;
	t_in_quote	state;

	init_quote_state(&state);
	i = 0;
	while (line[i])
	{
		swap_quote_state(&state, line[i]);
		if (line[i] == '|' && !state.inside)
		{
			if (!validate_pipes_2(line, i))
				return (0);
		}
		i++;
	}
	return (1);
}

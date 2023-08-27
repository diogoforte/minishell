/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 05:06:45 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/27 13:19:58 by bcastelo         ###   ########.fr       */
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

	if (!*line || only_spaces(line))
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
	int		valid;
	char	*clean;

	clean = ignore_in_quotes(line);
	valid = validate_red_2(clean);
	free(clean);
	return (valid);
}

int	validate_pipes(char *line)
{
	int		valid;
	char	*clean;

	clean = ignore_in_quotes(line);
	valid = validate_pipes_2(clean);
	free(clean);
	return (valid);
}

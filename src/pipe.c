/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/15 20:22:10 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	***parse_pipeline(char *line, char ***envp)
{
	int		i;
	int		num_commands;
	char	***parsed_pipeline;
	char	*trimmed_command;
	char	**commands;
	char	**tests;

	commands = ft_split(line, '|');
	tests = split_pipes(line, '|');
	ft_freematrix(tests);
	i = 0;
	num_commands = 0;
	while (commands[num_commands])
		num_commands++;
	parsed_pipeline = malloc((num_commands + 1) * sizeof(char **));
	while (commands[i])
	{
		trimmed_command = trim_spaces(commands[i]);
		parsed_pipeline[i] = parse_cmd(trimmed_command, envp);
		i++;
	}
	parsed_pipeline[i] = NULL;
	ft_freematrix(commands);
	return (parsed_pipeline);
}

char	*trim_spaces(char *str)
{
	char	*end_str;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end_str = str + ft_strlen(str) - 1;
	while (end_str > str && ft_isspace((unsigned char)*end_str))
		end_str--;
	end_str[1] = '\0';
	return (str);
}

void	handle_child(char ***cmds, int index, char ***envp)
{
	if (index)
	{
		dup2(get_pipe()->infile, 0);
		close(get_pipe()->infile);
	}
	if (cmds[index + 1])
	{
		dup2(get_pipe()->pipe[1], 1);
		close(get_pipe()->pipe[1]);
	}
	close(get_pipe()->pipe[0]);
	execute(cmds[index], envp);
	exit(EXIT_FAILURE);
}

void	handle_parent(int index)
{
	close(get_pipe()->pipe[1]);
	if (index)
		close(get_pipe()->infile);
	get_pipe()->infile = get_pipe()->pipe[0];
	if (index + 1)
		pipe(get_pipe()->pipe);
}

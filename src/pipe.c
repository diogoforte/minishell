/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 17:32:54 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*get_pipe(void)
{
	static t_pipe	pipe = {{0, 1}, -1, -1};

	return (&pipe);
}

char	***parse_pipeline(char *line, char ***envp)
{
	int		i;
	int		num_commands;
	char	***parsed_pipeline;
	char	*trimmed_command;
	char	**commands;

	commands = ft_split(line, '|');
	i = 0;
	num_commands = 0;
	while (commands[num_commands])
		num_commands++;
	parsed_pipeline = malloc((num_commands + 1) * sizeof(char **));
	if (!parsed_pipeline)
		return (NULL);
	while (commands[i])
	{
		trimmed_command = trim_spaces(commands[i]);
		parsed_pipeline[i] = NULL;
		parsed_pipeline[i] = resize_cmd(parsed_pipeline[i], i);
		parsed_pipeline[i] = parse_cmd(trimmed_command, envp);
		i++;
	}
	parsed_pipeline[i] = NULL;
	return (parsed_pipeline);
}

char	*trim_spaces(char *str)
{
	char	*end_str;

	while (isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end_str = str + strlen(str) - 1;
	while (end_str > str && isspace((unsigned char)*end_str))
		end_str--;
	end_str[1] = '\0';
	return (str);
}

void	reset_structs(void)
{
	if (get_redirections()->in_redir || get_redirections()->out_redir)
	{
		get_redirections()->in_redir = -1;
		get_redirections()->out_redir = -1;
		if (get_redirections()->in_file)
		{
			free(get_redirections()->in_file);
			get_redirections()->in_file = NULL;
		}
		if (get_redirections()->out_file)
		{
			free(get_redirections()->out_file);
			get_redirections()->out_file = NULL;
		}
		get_redirections()->heredoc = 0;
	}
	if (get_pipe()->infile || get_pipe()->outfile)
	{
		get_pipe()->infile = -1;
		get_pipe()->outfile = -1;
	}
}

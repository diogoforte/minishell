/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 02:03:21 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end(char *start)
{
	char	*end;
	t_in_quote	state;

	init_quote_state(&state);
	end = start;
	if (*start == '"' || *start == '\'')
	{
		swap_quote_state(&state, *end++);
		while (*end && (*end != ' ' || state.inside))
			swap_quote_state(&state, *end++);
	}
	else
	{
		while (*end && *end != ' ')
			end++;
	}
	return (end);
}

char	**resize_cmd(char **cmd, int count)
{
	char	**new_cmd;

	new_cmd = malloc((count + 2) * sizeof(char *));
	if (cmd)
	{
		ft_memcpy(new_cmd, cmd, count * sizeof(char *));
		free(cmd);
		cmd = NULL;
	}
	return (new_cmd);
}

char	*strip_quotes(char *arg)
{
	char	*clean;

	if (arg[0] == '"')
	{
		clean = remove_char(arg, '"');
		free(arg);
		return (clean);
	}
	else if (arg[0] == '\'')
	{
		clean = remove_char(arg, '\'');
		free(arg);
		return (clean);
	}
	else
		return (arg);
}

char	**parse_cmd(char *line, char ***envp)
{
	t_cmd_parser	parser;
	char			*tmp;

	tmp = line;
	if ((ft_strchr(line, '>') || ft_strchr(line, '<')) && !ft_strchr(line, ' '))
		line = insert_space(line);
	parser = (t_cmd_parser){NULL, line, line, 0, envp};
	while (*(parser.end))
	{
		parser.start = skip_spaces(parser.start);
		parser.end = find_end(parser.start);
		parser.start = process_cmd(&parser);
		parser.start = parser.end + 1;
	}
	parser.cmd = resize_cmd(parser.cmd, parser.i);
	parser.cmd[parser.i] = NULL;
	if ((ft_strchr(tmp, '>') || ft_strchr(tmp, '<')) && !ft_strchr(tmp, ' '))
		free(line);
	return (parser.cmd);
}

char	*skip_spaces(char *start)
{
	while (*start && *start == ' ')
		start++;
	return (start);
}

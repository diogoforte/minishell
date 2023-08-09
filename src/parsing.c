/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/09 16:00:15 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end(char *start)
{
	char	*end;
	char	quote;

	end = start;
	if (*start == '"' || *start == '\'')
	{
		quote = *start;
		end++;
		while (*end && *end != quote)
			end++;
		if (*end)
			end++;
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

void	strip_quotes(char *arg)
{
	char	*pos;
	char	*prev_char;
	char	*next_char;

	pos = ft_strpbrk(arg, "\"'");
	while (pos)
	{
		if (pos > arg)
			prev_char = pos - 1;
		else
			prev_char = NULL;
		if (pos < (arg + ft_strlen(arg) - 1))
			next_char = pos + 1;
		else
			next_char = NULL;
		if ((prev_char && *prev_char != *pos) || (next_char
				&& *next_char != *pos))
			ft_memmove(pos, pos + 1, ft_strlen(pos));
		else
			break ;
		pos = ft_strpbrk(arg, "\"'");
	}
}

char	**parse_cmd(char *line, char ***envp)
{
	t_cmd_parser	parser;

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
	return (parser.cmd);
}

char	*skip_spaces(char *start)
{
	while (*start && *start == ' ')
		start++;
	return (start);
}

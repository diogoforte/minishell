/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 16:16:01 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end(char *start)
{
	char		*end;
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

t_redirect	*parse_cmd(char *line, char ***envp)
{
	char		*tmp;
	t_redirect	*head;

	tmp = line;
	line = preprocess_line(line);
	head = parse_redirections(line, envp);
	if ((ft_strchr(tmp, '>') || ft_strchr(tmp, '<')) && !ft_strchr(tmp, ' '))
		free(line);
	return (head);
}

t_redirect	*parse_redirections(char *line, char ***envp)
{
	t_cmd_parser	parser;
	t_redirect		*head;
	t_redirect		*current;

	head = NULL;
	current = NULL;
	parser = (t_cmd_parser){NULL, line, line, 0, envp};
	while (*(parser.end))
	{
		parser.start = skip_spaces(parser.start);
		if (*parser.start == '\0')
			break ;
		parser.end = find_end(parser.start);
		if (!current)
		{
			current = init_redirect();
			head = current;
		}
		process_cmd(&parser, &current);
		parser.start = parser.end + 1;
	}
	return (head);
}

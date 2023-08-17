/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 22:00:00 by dinunes-         ###   ########.fr       */
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

int	is_redirection(char *start)
{
	if (!ft_strncmp(start, ">", 1) || !ft_strncmp(start, ">>", 2)
		|| ft_strncmp(start, "<<", 2) == 0 || ft_strncmp(start, "<", 1) == 0)
	{
		return (1);
	}
	return (0);
}

t_redirect	*parse_cmd(char *line, char ***envp)
{
	t_cmd_parser	parser;
	char			*tmp;
	t_redirect		*head;
	t_redirect		*current;

	head = NULL;
	current = NULL;
	tmp = line;
	if ((ft_strchr(line, '>') || ft_strchr(line, '<')) && !ft_strchr(line, ' '))
		line = insert_space(line);
	parser = (t_cmd_parser){NULL, line, line, 0, envp};
	while (*(parser.end))
	{
		parser.start = skip_spaces(parser.start);
		if (*parser.start == '\0')
			break ;
		parser.end = find_end(parser.start);
		if (is_redirection(parser.start))
		{
			if (!current)
			{
				current = init_redirect();
				head = current;
			}
		}
		else
		{
			if (!current)
			{
				current = init_redirect();
				head = current;
			}
		}
		process_cmd(&parser, &current);
		parser.start = parser.end + 1;
	}
	if ((ft_strchr(tmp, '>') || ft_strchr(tmp, '<')) && !ft_strchr(tmp, ' '))
		free(line);
	return (head);
}

char	*skip_spaces(char *start)
{
	while (*start && *start == ' ')
		start++;
	return (start);
}

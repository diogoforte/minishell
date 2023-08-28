/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/28 17:53:50 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end(char *start)
{
	char		*end;
	t_in_quote	state;

	init_quote_state(&state);
	end = start;
	while (*end)
	{
		swap_quote_state(&state, *end);
		if (*end == ' ' && !state.inside)
			return (end);
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
	int		i;
	char	*start;

	start = arg;
	clean = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!clean)
		return (arg);
	while (*arg)
	{
		if (*arg == '"' || *arg == '\'')
			arg = remove_char(arg, clean, *arg);
		else
		{
			i = ft_strlen(clean);
			clean[i] = *arg;
			arg++;
		}
	}
	free(start);
	return (clean);
}

t_redirect	*parse_cmd(char *line, char ***envp)
{
	char		*tmp;
	t_redirect	*head;

	line = skip_spaces(line);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 00:10:03 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*process_cmd(t_cmd_parser *parser)
{
	if (!ft_strncmp(parser->start, ">", 1) || !ft_strncmp(parser->start, ">>",
			2))
	{
		get_redirections()->command = *parser->cmd;
		parser->start = process_redirection_out(parser);
	}
	else if (ft_strncmp(parser->start, "<<", 2) == 0)
		parser->start = process_redirection_in_heredoc(parser);
	else if (ft_strncmp(parser->start, "<", 1) == 0)
		parser->start = process_redirection_in(parser);
	else
		parser->start = process_regular_cmd(parser);
	return (parser->start);
}

char	*process_redirection_out(t_cmd_parser *parser)
{
	char		*word;
	t_redirect	*redir;

	if (*(parser->start) == '>' && *((parser->start) + 1) != '>')
	{
		get_redirections()->out_redir = 1;
		parser->start++;
	}
	else
	{
		get_redirections()->out_redir = 2;
		parser->start += 2;
	}
	parser->start = skip_spaces(parser->start);
	parser->end = find_end(parser->start);
	word = ft_calloc(parser->end - parser->start + 1, sizeof(char));
	redir = get_redirections();
	redir->out_file = ft_strncpy(word,
			parser->start, parser->end - parser->start);
	redir->out_file[parser->end - parser->start] = '\0';
	return (parser->start);
}

char	*process_redirection_in(t_cmd_parser *parser)
{
	char		*word;
	t_redirect	*redir;

	redir = get_redirections();
	redir->in_redir = 1;
	parser->start++;
	parser->start = skip_spaces(parser->start);
	parser->end = find_end(parser->start);
	word = ft_calloc(parser->end - parser->start + 1, sizeof(char));
	redir->in_file = ft_strncpy(word, parser->start,
			parser->end - parser->start);
	redir->in_file[parser->end - parser->start] = '\0';
	return (parser->start);
}

char	*process_redirection_in_heredoc(t_cmd_parser *parser)
{
	t_redirect	*redir;

	redir = get_redirections();
	redir->in_redir = 2;
	while (*parser->start == '<' || *parser->start == ' ')
		parser->start++;
	parser->end = find_end(parser->start);
	redir->heredoc = create_heredoc_file(parser->start, parser->envp);
	return (parser->start);
}

char	*process_regular_cmd(t_cmd_parser *parser)
{
	parser->cmd = resize_cmd(parser->cmd, parser->i);
	(parser->cmd)[parser->i] = ft_strncpy(malloc(parser->end - parser->start
				+ 1), parser->start, parser->end - parser->start);
	(parser->cmd)[parser->i][parser->end - parser->start] = '\0';
	(parser->cmd)[parser->i] = assign_variable((parser->cmd)[parser->i],
			parser->envp, 1);
	(parser->cmd)[parser->i] = strip_quotes((parser->cmd)[parser->i]);
	(parser->i)++;
	return (parser->start);
}

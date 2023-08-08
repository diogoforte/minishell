/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/08 17:21:28 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*process_cmd(t_cmd_parser *parser)
{
	if (!ft_strncmp(parser->start, ">", 1) || !ft_strncmp(parser->start, ">>",
			2))
		parser->start = process_redirection_out(parser);
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
	get_redirections()->out_file = ft_strncpy(malloc(parser->end - parser->start + 1),
			parser->start, parser->end - parser->start);
	get_redirections()->out_file[parser->end - parser->start] = '\0';
	return (parser->start);
}

char	*process_redirection_in(t_cmd_parser *parser)
{
	get_redirections()->in_redir = 1;
	parser->start++;
	parser->start = skip_spaces(parser->start);
	parser->end = find_end(parser->start);
	get_redirections()->in_file = ft_strncpy(malloc(parser->end - parser->start + 1),
			parser->start, parser->end - parser->start);
	get_redirections()->in_file[parser->end - parser->start] = '\0';
	return (parser->start);
}

char	*process_redirection_in_heredoc(t_cmd_parser *parser)
{
	get_redirections()->in_redir = 2;
	parser->start = parser->start + 2;
	parser->end = find_end(parser->start);
	get_redirections()->heredoc = create_heredoc_file(parser->start, parser->envp);
	return (parser->start);
}

char	*process_regular_cmd(t_cmd_parser *parser)
{
	parser->cmd = resize_cmd(parser->cmd, parser->i);
	(parser->cmd)[parser->i] = ft_strncpy(malloc(parser->end - parser->start
				+ 1), parser->start, parser->end - parser->start);
	(parser->cmd)[parser->i][parser->end - parser->start] = '\0';
	(parser->cmd)[parser->i] = assign_variable((parser->cmd)[parser->i],
			parser->envp);
	strip_quotes((parser->cmd)[parser->i]);
	(parser->i)++;
	return (parser->start);
}

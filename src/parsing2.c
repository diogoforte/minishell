/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 17:35:40 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*process_cmd(char *start, char **end, char ***cmd, int *i, char ***envp)
{
	if (!ft_strncmp(start, ">", 1) || !ft_strncmp(start, ">>", 2))
		start = process_redirection_out(start, end);
	else if (ft_strncmp(start, "<<", 2) == 0)
		start = process_redirection_in_heredoc(start, end, envp);
	else if (ft_strncmp(start, "<", 1) == 0)
		start = process_redirection_in(start, end);
	else
		start = process_regular_cmd(start, end, cmd, i, envp);
	return (start);
}

char	*process_redirection_out(char *start, char **end)
{
	t_redirect	*redir;

	redir = get_redirections();
	if (*start == '>' && *(start + 1) != '>')
	{
		redir->out_redir = 1;
		start++;
	}
	else
	{
		redir->out_redir = 2;
		start += 2;
	}
	start = skip_spaces(start);
	*end = find_end(start);
	redir->out_file = ft_strncpy(malloc(*end - start + 1), start, *end - start);
	redir->out_file[*end - start] = '\0';
	return (start);
}

char	*process_redirection_in(char *start, char **end)
{
	t_redirect	*redir;

	redir = get_redirections();
	redir->in_redir = 1;
	start++;
	start = skip_spaces(start);
	*end = find_end(start);
	redir->in_file = ft_strncpy(malloc(*end - start + 1), start, *end - start);
	redir->in_file[*end - start] = '\0';
	return (start);
}

char	*process_redirection_in_heredoc(char *start, char **end, char ***envp)
{
	get_redirections()->in_redir = 2;
	start = start + 2;
	*end = find_end(start);
	get_redirections()->heredoc = create_heredoc_file(start, envp);
		return (start);
}

char	*process_regular_cmd(char *start, char **end, char ***cmd, int *i,
		char ***envp)
{
	*cmd = resize_cmd(*cmd, *i);
	(*cmd)[*i] = ft_strncpy(malloc(*end - start + 1), start, *end - start);
	(*cmd)[*i][*end - start] = '\0';
	(*cmd)[*i] = assign_variable((*cmd)[*i], envp);
	strip_quotes((*cmd)[*i]);
	(*i)++;
	return (start);
}

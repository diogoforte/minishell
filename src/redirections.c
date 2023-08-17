/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:55:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 17:50:54 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input_redirection(t_redirect *redir)
{
	int	in_fd;

	in_fd = -1;
	if (redir->in_redir == 2 && redir->heredoc)
	{
		in_fd = open("/tmp/heredoc_file", O_RDONLY);
		if (in_fd < 0)
		{
			perror("Error opening heredoc file");
			exit(0);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (redir->in_redir && redir->in_file)
	{
		in_fd = open(redir->in_file, O_RDONLY);
		if (in_fd < 0)
		{
			perror("Error opening input file");
			exit(0);
		}
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

void	handle_output_redirection(t_redirect *redir)
{
	int	out_fd;

	out_fd = -1;
	if (redir->out_redir && redir->out_file)
	{
		if (redir->out_redir == 1)
			out_fd = open(redir->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir->out_redir == 2)
			out_fd = open(redir->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd < 0)
		{
			perror("Error opening output file");
			exit(0);
		}
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

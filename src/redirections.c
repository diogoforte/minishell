/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:55:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/10 14:08:11 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_input_redirection(void)
{
	int	in_fd;

	in_fd = -1;
	if (get_redirections()->in_redir == 2 && get_redirections()->heredoc)
	{
		in_fd = open("/tmp/heredoc_file", O_RDONLY);
		if (in_fd < 0)
			perror("Error opening heredoc file");
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	else if (get_redirections()->in_redir && get_redirections()->in_file)
	{
		in_fd = open(get_redirections()->in_file, O_RDONLY);
		if (in_fd < 0)
			perror("Error opening input file");
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

void	handle_output_redirection(void)
{
	int	out_fd;

	out_fd = -1;
	if (get_redirections()->out_redir && get_redirections()->out_file)
	{
		if (get_redirections()->out_redir == 1)
			out_fd = open(get_redirections()->out_file,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (get_redirections()->out_redir == 2)
			out_fd = open(get_redirections()->out_file,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (out_fd < 0)
			perror("Error opening output file");
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:05:43 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/10 18:44:29 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*get_pipe(void)
{
	static t_pipe	pipe = {{0, 1}, -1, -1};

	return (&pipe);
}

t_redirect	*get_redirections(void)
{
	static t_redirect	redirections = {0, 0, 0, NULL, NULL, NULL};

	return (&redirections);
}

void	reset_structs(void)
{
	reset_redirections();
	reset_pipe();
}

void	reset_redirections(void)
{
	get_redirections()->in_redir = -1;
	get_redirections()->out_redir = -1;
	if (get_redirections()->in_file)
	{
		free(get_redirections()->in_file);
		get_redirections()->in_file = NULL;
	}
	if (get_redirections()->out_file)
	{
		free(get_redirections()->out_file);
		get_redirections()->out_file = NULL;
	}
	get_redirections()->heredoc = 0;
	get_redirections()->command = NULL;
}

void	reset_pipe(void)
{
	get_pipe()->infile = -1;
	get_pipe()->outfile = -1;
}

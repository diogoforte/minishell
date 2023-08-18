/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:05:43 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 22:36:46 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*get_pipe(void)
{
	static t_pipe	pipe = {{0, 1}, -1, -1};

	return (&pipe);
}

void	reset_structs(t_redirect *head)
{
	reset_redirections(head);
	reset_pipe();
}

void	reset_redirections(t_redirect *head)
{
	t_redirect	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		ft_freematrix(tmp->cmd);
		free(tmp->in_file);
		free(tmp->out_file);
		free(tmp);
	}
}

void	reset_pipe(void)
{
	get_pipe()->infile = -1;
	get_pipe()->outfile = -1;
}

t_redirect	*init_redirect(void)
{
	t_redirect	*new_redirect;

	new_redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (new_redirect == NULL)
		return (NULL);
	new_redirect->cmd = NULL;
	new_redirect->cmd_count = 0;
	new_redirect->in_redir = 0;
	new_redirect->out_redir = 0;
	new_redirect->heredoc = 0;
	new_redirect->in_file = NULL;
	new_redirect->out_file = NULL;
	new_redirect->next = NULL;
	return (new_redirect);
}

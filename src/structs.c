/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:05:43 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/21 12:35:12 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reset(t_redirect *redirect, t_pipe *pipe, char *line)
{
	reset_redirections(redirect);
	reset_pipes(pipe);
	free(line);
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

void	reset_pipes(t_pipe *head)
{
	t_pipe	*tmp;

	while (head)
	{
		tmp = head->next;
		if (head->pipe[0] != -1)
			close(head->pipe[0]);
		if (head->pipe[1] != -1)
			close(head->pipe[1]);
		free(head);
		head = tmp;
	}
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
	new_redirect->in_fd = -1;
	new_redirect->out_fd = -1;
	return (new_redirect);
}

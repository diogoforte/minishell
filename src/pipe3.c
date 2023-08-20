/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 01:29:07 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/20 03:44:30 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_pipe	*initialize_pipeline(int n)
{
	t_pipe	*head;
	int		i;

	i = 0;
	head = NULL;
	while (i < n)
	{
		head = add_pipe(head);
		i++;
	}
	return (head);
}

t_pipe	*add_pipe(t_pipe *head)
{
	t_pipe	*new_node;
	t_pipe	*current;

	new_node = init_pipe();
	if (!new_node)
		return (NULL);
	if (!head)
	{
		return (new_node);
	}
	current = head;
	while (current->next)
	{
		current = current->next;
	}
	current->next = new_node;
	return (head);
}

t_pipe	*init_pipe(void)
{
	t_pipe	*new_node;

	new_node = malloc(sizeof(t_pipe));
	if (!new_node)
		return (NULL);
	new_node->pipe[0] = -1;
	new_node->pipe[1] = -1;
	new_node->infile = -1;
	new_node->outfile = -1;
	new_node->next = NULL;
	return (new_node);
}

t_pipe	*get_pipe(t_pipe *head, int n)
{
	int	i;

	i = 0;
	while (head && i < n)
	{
		head = head->next;
		i++;
	}
	return (head);
}

int	count_commands(t_redirect *cmds_head)
{
	int	i;

	i = 0;
	while (cmds_head)
	{
		i++;
		cmds_head = cmds_head->next;
	}
	return (i);
}

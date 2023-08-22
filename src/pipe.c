/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/22 11:05:03 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redirect	*parse_pipeline(char *line, char ***envp)
{
	int			i;
	char		**commands;
	t_redirect	*head;
	t_redirect	*current;
	t_redirect	*newnode;

	head = NULL;
	current = NULL;
	commands = split_pipes(line, '|');
	if (!commands)
		return (NULL);
	i = 0;
	while (commands[i])
	{
		newnode = parse_cmd(commands[i++], envp);
		if (!newnode)
			continue ;
		if (!head)
			head = newnode;
		else
			current->next = newnode;
		current = newnode;
	}
	ft_freematrix(commands);
	return (head);
}

char	*trim_spaces(char *str)
{
	char	*end_str;

	while (ft_isspace((unsigned char)*str))
		str++;
	if (*str == 0)
		return (str);
	end_str = str + ft_strlen(str) - 1;
	while (end_str > str && ft_isspace((unsigned char)*end_str))
		end_str--;
	end_str[1] = '\0';
	return (str);
}

void	handle_child(t_redirect **head, t_pipe *pipes_head,
			int index, char ***envp)
{
	t_redirect	*current;
	t_redirect	*cmds_head;
	t_pipe		*current_pipe;

	current = head[0];
	cmds_head = head[1];
	current_pipe = get_pipe(pipes_head, index);
	if (index != 0)
	{
		dup2(current_pipe->infile, 0);
		close(current_pipe->infile);
	}
	if (current->next)
	{
		dup2(current_pipe->pipe[1], 1);
		close(current_pipe->pipe[0]);
		close(current_pipe->pipe[1]);
	}
	execute(current, cmds_head, pipes_head, envp);
}

void	handle_parent(t_redirect *head, t_pipe *pipes_head, int index)
{
	t_redirect	*current;
	t_pipe		*current_pipe;

	current = head;
	current_pipe = get_pipe(pipes_head, index);
	if (current_pipe->pipe[1] != -1)
		close(current_pipe->pipe[1]);
	if (current->next)
	{
		current_pipe->next = add_pipe(current_pipe->next);
		if (current_pipe->next)
		{
			pipe(current_pipe->next->pipe);
			current_pipe->next->infile = current_pipe->pipe[0];
		}
	}
	if (index != 0 && current_pipe->infile != -1)
		close(current_pipe->infile);
}

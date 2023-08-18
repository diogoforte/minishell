/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 23:45:32 by bcastelo         ###   ########.fr       */
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

void	handle_child(t_redirect *head, int index, char ***envp)
{
	t_redirect	*current;
	int			i;

	current = head;
	i = 1;
	while (i < index && current && current->next)
	{
		current = current->next;
		i++;
	}
	if (!current)
		exit(EXIT_FAILURE);
	if (index != 0)
	{
		dup2(get_pipe()->infile, 0);
		close(get_pipe()->infile);
	}
	if (current && current->next)
		dup2(get_pipe()->pipe[1], 1);
	close(get_pipe()->pipe[0]);
	close(get_pipe()->pipe[1]);
	execute(current, envp);
	exit(EXIT_FAILURE);
}

void	handle_parent(t_redirect *head, int index)
{
	t_redirect	*current;
	int			i;

	current = head;
	i = 1;
	while (i < index && current && current->next)
	{
		current = current->next;
		i++;
	}
	close(get_pipe()->pipe[1]);
	if (index != 0)
		close(get_pipe()->infile);
	get_pipe()->infile = get_pipe()->pipe[0];
	if (current && current->next)
		pipe(get_pipe()->pipe);
}

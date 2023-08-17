/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 21:25:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redirect	*parse_pipeline(char *line, char ***envp)
{
	int			i;
	char		**commands;
	t_redirect	*head;
	t_redirect	*current;
	t_redirect	*newNode;

	head = NULL;
	current = NULL;
	commands = split_pipes(line, '|');
	i = 0;
	while (commands[i])
	{
		newNode = parse_cmd(commands[i], envp);
		if (!head)
		{
			head = newNode;
			current = head;
		}
		else
		{
			current->next = newNode;
			current = newNode;
		}
		i++;
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

void handle_child(t_redirect *head, int index, char ***envp)
{
	t_redirect *current;
	int i;

	current = head;
	i = 0;
	while (i < index && current)
	{
		current = current->next;
		i++;
	}
	if (!current)
		exit(EXIT_FAILURE);  // No command to run, exit child process

	if (index != 0)
	{
		dup2(get_pipe()->infile, 0);
		close(get_pipe()->infile);
	}
	if (current->next)
	{
		dup2(get_pipe()->pipe[1], 1);
		close(get_pipe()->pipe[1]);
	}
	close(get_pipe()->pipe[0]);  // Always close the read end in the child
	execute(current, envp);
	exit(EXIT_FAILURE);
}

void handle_parent(t_redirect *head, int index)
{
	t_redirect *current;
	int i;

	current = head;
	i = 0;
	while (i < index && current)
	{
		current = current->next;
		i++;
	}
	close(get_pipe()->pipe[1]);  // Always close the write end in the parent
	if (index != 0)
		close(get_pipe()->infile);

	get_pipe()->infile = get_pipe()->pipe[0];
	if (current && current->next)
		pipe(get_pipe()->pipe);
}

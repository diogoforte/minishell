/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 07:16:50 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redirect	*get_redirections(void)
{
	static t_redirect	redirections = {0, 0, 0, NULL, NULL};

	return (&redirections);
}

void	reset_redirections(void)
{
	t_redirect	*redirections;

	redirections = get_redirections();
	redirections->in_redir = 0;
	redirections->out_redir = 0;
	if (redirections->in_file)
	{
		free(redirections->in_file);
		redirections->in_file = NULL;
	}
	if (redirections->out_file)
	{
		free(redirections->out_file);
		redirections->out_file = NULL;
	}
	redirections->heredoc = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**new_envp;

	(void)ac;
	(void)av;
	line = 0;
	new_envp = dup_envp(envp);
	signal(2, handle_sigint);
	while (1)
	{
		line = readline("minishell~$ ");
		if (line == NULL)
			exit(0);
		parsing(line, &new_envp);
		reset_redirections();
		free(line);
	}
}

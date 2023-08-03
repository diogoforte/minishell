/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 09:15:16 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_redirect	*get_redirections(void)
{
	static t_redirect	redirections = {0, 0, 0, NULL, NULL};

	return (&redirections);
}

int	*exit_status(int *value)
{
	static int	status;

	status = 0;
	if (value)
		status = *value;
	return (&status);
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
	char	**cmd;

	(void)ac;
	(void)av;
	line = 0;
	new_envp = env_add(&envp, NULL);
	signal(2, handle_sigint);
	while (1)
	{
		line = readline("minishell~$ ");
		if (line == NULL)
			exit(0);
		reset_redirections();
		cmd = parse_cmd(line, &new_envp);
		if (cmd)
			execute(cmd, &new_envp);
		ft_freematrix(cmd);
		free(line);
	}
}

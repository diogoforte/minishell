/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 14:08:50 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

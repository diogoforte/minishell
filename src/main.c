/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/07 12:18:07 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**new_envp;
	char	***cmds;

	(void)ac;
	(void)av;
	line = NULL;
	new_envp = env_add(&envp, NULL);
	signal(2, handle_sigint);
	while (1)
	{
		line = readline("minishell~$ ");
		if (!line) 
		{
			rl_clear_history();
			exit(0);
		}
		if (line && *line) 
			add_history(line);
		reset_structs();
		cmds = parse_pipeline(line, &new_envp);
		pipe(get_pipe()->pipe);
		execute_pipeline(cmds, &new_envp);
		printf("\n");
		ft_freetensor(cmds);
		free(line);
	}
}

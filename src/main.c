/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 17:36:02 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	t_redirect	*cmds_head;
	t_pipe		*pipes_head;
	t_heredoc	heredoc;
	char		*line;
	char		**new_envp;

	(void)ac;
	(void)av;
	new_envp = env_add(&envp, NULL);
	heredoc.envp = &new_envp;
	while (1)
	{
		signals(0);
		line = read_line(new_envp);
		if (!check_input(line))
			continue ;
		cmds_head = parse_pipeline(line, &new_envp, heredoc);
		signals(1);
		pipes_head = initialize_pipeline(count_commands(cmds_head));
		execute_pipeline(cmds_head, pipes_head, &new_envp);
		reset(cmds_head, pipes_head, line);
	}
}

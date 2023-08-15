/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/15 17:08:46 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_prompt(void)
{
	printf("%s@minishell", search_env(get_envp(NULL), "USER"));
}

char	*read_line(char **envp)
{
	char	*line;

	line = NULL;
	line = readline("$> ");
	if (!line)
	{
		ft_freematrix(envp);
		rl_clear_history();
		exit(0);
	}
	return (line);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**new_envp;
	char	***cmds;

	(void)ac;
	(void)av;
	new_envp = env_add(&envp, NULL);
	while (1)
	{
		get_envp(&new_envp);
		signals(0);
		print_prompt();
		line = read_line(new_envp);
		if (line && *line)
			add_history(line);
		reset_structs();
		cmds = parse_pipeline(line, &new_envp);
		pipe(get_pipe()->pipe);
		signals(1);
		execute_pipeline(cmds, &new_envp);
		ft_freetensor(cmds);
		free(line);
	}
}

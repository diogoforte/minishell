/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/10 23:43:48 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_prompt(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s┌──(%s%s㉿minishell%s%s)-[%s%s%s%s]\n", GREEN, BOLD_BLUE,
		search_env(get_envp(NULL), "USER"), RESET, GREEN, BOLD_WHITE,
		pwd, RESET, GREEN);
	free(pwd);
}

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**new_envp;
	char	***cmds;

	(void)ac;
	(void)av;
	line = NULL;
	new_envp = env_add(&envp, NULL);
	while (1)
	{
		get_envp(&new_envp);
		signals(0);
		print_prompt();
		line = readline("└─\033[1;34m$\033[0m ");
		if (!line)
		{
			ft_freematrix(new_envp);
			rl_clear_history();
			exit(0);
		}
		if (line && *line)
			add_history(line);
		reset_structs();
		cmds = parse_pipeline(line, &new_envp);
		pipe(get_pipe()->pipe);
		signals(1);
		execute_pipeline(cmds, &new_envp);
		printf("\n");
		ft_freetensor(cmds);
		free(line);
	}
}

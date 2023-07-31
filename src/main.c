/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 22:55:13 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **envp)
{
	char	*line;
	char	**new_envp;

	line = 0;
	(void)ac;
	(void)av;
	new_envp = dup_envp(envp);
	signal(2, handle_sigint);
	while (1)
	{
		line = readline("minishell~$ ");
		if (line == NULL)
			exit(0);
		parsing(line, &new_envp);
		free(line);
	}
}

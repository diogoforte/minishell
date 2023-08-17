/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/17 21:58:40 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*read_line(char **envp)
{
	char	*line;

	line = NULL;
	line = readline("minishell$> ");
	if (!line)
	{
		ft_freematrix(envp);
		rl_clear_history();
		exit(0);
	}
	return (line);
}

void	print_redirect_params(const t_redirect *redir)
{
	int	i;

	i = 0;
	while (redir->cmd[i])
	{
		printf("cmd[%d]%s \n", i, redir->cmd[i]);
		i++;
	}
	printf("in_redir: %d\n", redir->in_redir);
	printf("out_redir: %d\n", redir->out_redir);
	printf("heredoc: %d\n", redir->heredoc);
	printf("in_file: %s\n", redir->in_file);
	printf("out_file: %s\n", redir->out_file);
	if (redir->next)
	{
		printf("\n---> Next Redirect Structure: \n");
		print_redirect_params(redir->next);
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	char		**new_envp;
	t_redirect	*cmds_head;

	(void)ac;
	(void)av;
	cmds_head = NULL;
	new_envp = env_add(&envp, NULL);
	while (1)
	{
		signals(0);
		line = read_line(new_envp);
		if (line && *line)
			add_history(line);
		cmds_head = parse_pipeline(line, &new_envp);
		pipe(get_pipe()->pipe);
		signals(1);
		execute_pipeline(cmds_head, &new_envp);
		reset_structs(cmds_head);
		free(line);
	}
}

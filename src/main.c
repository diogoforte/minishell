/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 05:13:48 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/23 21:22:08 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	printf("in_fd: %d\n", redir->in_fd);
	printf("out_fd: %d\n", redir->out_fd);
	if (redir->next)
	{
		printf("\n---> Next Redirect Structure: \n");
		print_redirect_params(redir->next);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_redirect	*cmds_head;
	t_pipe		*pipes_head;
	char		*line;
	char		**new_envp;

	(void)ac;
	(void)av;
	cmds_head = NULL;
	pipes_head = NULL;
	new_envp = env_add(&envp, NULL);
	while (1)
	{
		signals(0);
		line = read_line(new_envp);
		if (line && *line)
			add_history(line);
		if (!check_input(line))
			continue ;
		cmds_head = parse_pipeline(line, &new_envp);
		signals(1);
		pipes_head = initialize_pipeline(count_commands(cmds_head));
		execute_pipeline(cmds_head, pipes_head, &new_envp);
		reset(cmds_head, pipes_head, line);
		new_envp = env_sort(&new_envp);
	}
}

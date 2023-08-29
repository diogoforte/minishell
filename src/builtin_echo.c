/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:25:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:26:29 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	flag;

	flag = 0;
	if (*cmd && check_echo_flag(*cmd))
	{
		cmd++;
		flag = 1;
	}
	while (*cmd)
	{
		printf("%s", *cmd++);
		if (*cmd)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	ft_freematrix(*envp);
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

int	check_echo_flag(char *cmd)
{
	if (ft_strncmp(cmd, "-n", 2))
		return (0);
	cmd++;
	while (*cmd)
	{
		if (*cmd != 'n')
			return (0);
		cmd++;
	}
	return (1);
}

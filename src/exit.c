/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/28 10:24:46 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*exit_status(int *value)
{
	static int	status;

	if (value != NULL)
		status = *value;
	return (&status);
}

void	handle_exit_status(int *status)
{
	while (wait(status) > 0)
	{
		waitpid(-1, status, 0);
		if (WIFEXITED(*status))
		{
			*status = WEXITSTATUS(*status);
			exit_status(status);
		}
	}
}

void	exit_execve(t_redirect *cmds_head,
					t_pipe *pipes_head,
					char ***envp,
					int status)
{
	ft_freematrix(*envp);
	reset(cmds_head, pipes_head, NULL);
	exit(status);
}

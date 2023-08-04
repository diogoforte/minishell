/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/04 07:43:18 by dinunes-         ###   ########.fr       */
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

void	handle_exit_status(int *status, char ***envp)
{
	(void)envp;
	waitpid(-1, status, 0);
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		exit_status(status);
	}
	printf("\n");
}
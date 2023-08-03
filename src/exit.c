/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 13:37:06 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	*exit_status(int *value)
{
	static int	status;

	status = 0;
	if (value)
		status = *value;
	return (&status);
}

void	handle_exit_status(int *status, char ***envp)
{
	char	*statusstr;
	char	*final;

	waitpid(-1, status, 0);
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		statusstr = ft_itoa(*status);
		final = ft_strjoin("?=", statusstr);
		exit_status(status);
		*envp = env_remove(envp, "?");
		*envp = env_add(envp, final);
		free(statusstr);
		free(final);
	}
	printf("\n");
}

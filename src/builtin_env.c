/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:24:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:27:04 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	env(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	int		i;
	char	*ptr;

	i = 0;
	while ((*envp)[i])
	{
		ptr = ft_strchr((*envp)[i], '=');
		if (ptr)
			printf("%s\n", (*envp)[i]);
		i++;
	}
	ft_freematrix(*envp);
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

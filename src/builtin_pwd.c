/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:24:15 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:27:13 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	char	pwd[PATH_MAX];

	ft_freematrix(*envp);
	getcwd(pwd, PATH_MAX);
	if (!*pwd)
	{
		ft_dprintf(2, "Error: %s\n", strerror(errno));
		reset(cmds_head, pipes_head, NULL);
		exit(1);
	}
	else
		printf("%s\n", pwd);
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

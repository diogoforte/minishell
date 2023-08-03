/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 12:20:11 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pathfinder(char *cmd, char ***envp)
{
	int		i;
	char	**paths;
	char	*str;

	if (!cmd || !access(cmd, F_OK))
		return (cmd);
	i = 0;
	while (ft_strncmp((*envp)[i], "PATH", 4))
		i++;
	paths = ft_split((*envp)[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		str = ft_triplejoin(paths[i++], "/", cmd);
		if (!access(str, F_OK))
			break ;
		free(str);
		str = NULL;
	}
	ft_freematrix(paths);
	return (str);
}

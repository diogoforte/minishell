/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/11 13:58:12 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*pathfinder(char *cmd, char ***envp)
{
	int		i;
	char	**paths;
	char	*str;

	if (cmd && !access(cmd, F_OK))
		return (cmd);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "PATH", 4))
		i++;
	if (!(*envp)[i])
		return (NULL);
	paths = ft_split((*envp)[i] + 5, ':');
	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		str = ft_triplejoin(paths[i], "/", cmd);
		if (str && !access(str, F_OK))
			break ;
		free(str);
		i++;
	}
	ft_freematrix(paths);
	return (str);
}

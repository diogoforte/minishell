/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/15 00:32:53 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*cmd_found(char *str, char **paths)
{
	ft_freematrix(paths);
	return (str);
}

char	*pathfinder(char *cmd, char ***envp)
{
	int		i;
	char	**paths;
	char	*str;

	if (cmd && !access(cmd, X_OK))
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
		if (str && !access(str, X_OK))
			return (cmd_found(str, paths));
		free(str);
		i++;
	}
	ft_freematrix(paths);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 09:40:08 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*cmd_found(char *str, char **paths)
{
	ft_freematrix(paths);
	return (str);
}

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

int	executable_path(char *cmd)
{
	if (!ft_strncmp("./", cmd, 2) && !access(cmd, F_OK))
		return (1);
	if (cmd[0] == '/' && !access(cmd, F_OK))
		return (1);
	return (0);
}

int	path_exists(char *cmd)
{
	return (0);
	if (!access(cmd, F_OK) && access(cmd, X_OK))
	{
		ft_dprintf(2, "minishell: '%s': Permission denied\n", *cmd);
		return (1);
	}
	return (0);
}

char	*pathfinder(char *cmd, char ***envp)
{
	int		i;
	char	**paths;
	char	*str;

	if (cmd && executable_path(cmd))
		return (cmd);
	i = 0;
	while ((*envp)[i] && ft_strncmp((*envp)[i], "PATH", 4))
		i++;
	if (!(*envp)[i] || !*cmd)
		return (NULL);
	paths = ft_split((*envp)[i] + 5, ':');
	if (!paths || !paths[0])
		return (NULL);
	i = 0;
	while (paths[i])
	{
		str = ft_triplejoin(paths[i], "/", cmd);
		if (str && !access(str, F_OK))
			return (cmd_found(str, paths));
		free(str);
		i++;
	}
	ft_freematrix(paths);
	return (NULL);
}

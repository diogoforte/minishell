/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 02:32:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/01 17:30:57 by dinunes-         ###   ########.fr       */
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
		str = triple_strjoin(paths[i++], "/", cmd);
		if (!access(str, F_OK))
			break ;
		free(str);
		str = NULL;
	}
	if (!str)
		printf("Error: %s\n", strerror(errno));
	free_list(paths);
	return (str);
}

char	*triple_strjoin(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = 0;
	return (res);
}

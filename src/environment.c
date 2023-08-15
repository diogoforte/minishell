/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:55:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/15 17:12:45 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*search_env(char ***envp, char *cmd)
{
	int	i;
	int	len;

	len = ft_strlen(cmd);
	i = 0;
	if (!cmd)
		return (NULL);
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], cmd, len) && (*envp)[i][len] == '=')
			return (&(*envp)[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	**env_add(char ***envp, char *cmd)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while ((*envp)[i])
		i++;
	new_envp = malloc((i + 2) * sizeof(char *));
	while (j < i)
	{
		new_envp[j] = ft_strdup((*envp)[j]);
		j++;
	}
	if (cmd)
	{
		new_envp[j++] = ft_strdup(cmd);
		ft_freematrix(*envp);
	}
	new_envp[j] = NULL;
	return (new_envp);
}

char	**env_remove(char ***envp, char *cmd)
{
	char	**new_envp;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], cmd, ft_strlen(cmd)))
			k++;
		i++;
	}
	new_envp = malloc((i - k + 1) * sizeof(char *));
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], cmd, ft_strlen(cmd)))
			new_envp[j++] = ft_strdup((*envp)[i]);
		i++;
	}
	new_envp[j] = NULL;
	ft_freematrix(*envp);
	return (new_envp);
}

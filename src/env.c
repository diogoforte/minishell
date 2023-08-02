/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 15:55:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 07:27:03 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_env(char ***envp, char *cmd)
{
	int	i;
	int	len;

	len = ft_strlen(cmd);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], cmd, len) == 0 && (*envp)[i][len] == '=')
			return (&(*envp)[i][len + 1]);
		i++;
	}
	return (NULL);
}

char	*assign_variable(char *cmd, char ***envp)
{
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
	char	*new_cmd;
	int		open_quotes;
	int		apostrophe;
	char	*tmp;

	open_quotes = 0;
	apostrophe = 0;
	tmp = cmd;
	while (*tmp)
	{
		if (*tmp == '\'')
			open_quotes = !open_quotes;
		tmp++;
	}
	if (open_quotes)
		return (cmd);
	tmp = cmd;
	while (*tmp)
	{
		if (*tmp == '\'')
		{
			apostrophe = 1;
			break ;
		}
		tmp++;
	}
	if (apostrophe)
		return (cmd);
	var_start = ft_strchr(cmd, '$');
	if (var_start)
	{
		var_end = var_start + 1;
		while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
			var_end++;
		var_name = ft_strncpy(malloc(var_end - var_start), var_start + 1,
				var_end - var_start - 1);
		var_name[var_end - var_start - 1] = '\0';
		var_value = get_env(envp, var_name);
		if (var_value == NULL)
			var_value = "";
		new_cmd = malloc(strlen(cmd) - strlen(var_name) - 1 + strlen(var_value)
				+ 1);
		ft_strncpy(new_cmd, cmd, var_start - cmd);
		new_cmd[var_start - cmd] = '\0';
		ft_strcat(new_cmd, var_value);
		ft_strcat(new_cmd, var_end);
		return (assign_variable(new_cmd, envp));
	}
	return (cmd);
}

char	**dup_envp(char **envp)
{
	int		i;
	int		j;
	char	**new_envp;

	i = 0;
	j = 0;
	while (envp[i])
		i++;
	new_envp = malloc((i + 1) * sizeof(char *));
	while (j < i)
	{
		new_envp[j] = ft_strdup(envp[j]);
		j++;
	}
	new_envp[i] = NULL;
	return (new_envp);
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
	new_envp[j] = ft_strdup(cmd);
	new_envp[j + 1] = NULL;
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
		if (ft_strncmp((*envp)[i], cmd, ft_strlen(cmd)) == 0)
			k++;
		i++;
	}
	new_envp = malloc((i - k + 1) * sizeof(char *));
	if (!new_envp)
		return (NULL);
	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], cmd, ft_strlen(cmd)) != 0)
			new_envp[j++] = ft_strdup((*envp)[i]);
		free((*envp)[i]);
		i++;
	}
	new_envp[j] = NULL;
	*envp = new_envp;
	return (new_envp);
}

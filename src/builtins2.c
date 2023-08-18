/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:28:39 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/18 22:13:10 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_env(char *var)
{
	if (!ft_isalpha(var[0]))
	{
		printf("export: `%s': not a valid identifier\n", var);
		return (0);
	}
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var))
		{
			printf("export: `%s': not a valid identifier\n", var);
			return (0);
		}
		var++;
	}
	return (1);
}

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error: %s\n", strerror(errno));
		exit(1);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	exit(0);
}

void	env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
		printf("%s\n", (*envp)[i++]);
	exit(0);
}

void	export(char **cmd, char ***envp)
{
	int		i;
	int		status;
	char	**tmp;

	i = 0;
	status = 0;
	if (!*cmd)
	{
		while ((*envp)[i])
			printf("export %s\n", (*envp)[i++]);
		exit_status(&status);
		return ;
	}
	i = -1;
	while (cmd[++i])
	{
		if (!check_env(cmd[i]))
			continue ;
		tmp = ft_split(cmd[i], '=');
		if (search_env(envp, tmp[0]))
			*envp = env_remove(envp, tmp[0]);
		ft_freematrix(tmp);
		*envp = env_add(envp, cmd[i]);
	}
	exit_status(&status);
}

void	unset(char **cmd, char ***envp)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!*cmd)
	{
		exit_status(&status);
		return ;
	}
	while (cmd[i])
	{
		*envp = env_remove(envp, cmd[i]);
		i++;
	}
	exit_status(&status);
}

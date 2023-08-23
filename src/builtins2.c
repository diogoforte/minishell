/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:28:39 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/23 20:35:02 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	pwd(t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	char	*pwd;

	ft_freematrix(*envp);
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("Error: %s\n", strerror(errno));
		reset(cmds_head, pipes_head, NULL);
		exit(1);
	}
	else
	{
		printf("%s\n", pwd);
		free(pwd);
	}
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

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
			printf("declare -x %s\n", (*envp)[i++]);
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

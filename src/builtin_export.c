/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:25:06 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:58:04 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_variable(char **tmp)
{
	int	j;

	j = 1;
	if (tmp[1] && tmp[2])
	{
		printf("declare -x %s=\"", tmp[0]);
		while (tmp[j] && tmp[j + 1])
		{
			if (j == 1)
				printf("%s", tmp[j]);
			else
				printf("=%s", tmp[j]);
			j++;
		}
		printf("=%s\"\n", tmp[j]);
	}
	else
	{
		if (tmp[1])
			printf("declare -x %s=\"%s\"\n", tmp[0], tmp[1]);
		else
			printf("declare -x %s\n", tmp[0]);
	}
}

void	print_sorted_envp(char ***envp)
{
	int		i;
	char	**tmp;
	char	**sorted_envp;

	i = -1;
	sorted_envp = env_sort(*envp);
	while (sorted_envp[++i])
	{
		tmp = ft_split(sorted_envp[i], '=');
		print_variable(tmp);
		ft_freematrix(tmp);
	}
	ft_freematrix(sorted_envp);
}

void	export(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	status;

	status = 0;
	if (!*cmd)
	{
		print_sorted_envp(envp);
		exit_status(&status);
	}
	else
	{
		export_value(cmd, envp);
	}
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

int	check_export(char *var)
{
	int	status;

	status = 0;
	if (!ft_isalpha(var[0]) && var[0] != '_')
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", var);
		status = 1;
		exit_status(&status);
		return (0);
	}
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
		{
			ft_dprintf(2, "export: `%s': not a valid identifier\n", var);
			status = 1;
			exit_status(&status);
			return (0);
		}
		var++;
	}
	return (1);
}

void	export_value(char **cmd, char ***envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (cmd[++i])
	{
		if (!check_export(cmd[i]))
			continue ;
		tmp = ft_split(cmd[i], '=');
		if (search_env(envp, tmp[0]))
			*envp = env_remove(envp, tmp[0]);
		ft_freematrix(tmp);
		*envp = env_add(envp, cmd[i]);
	}
}

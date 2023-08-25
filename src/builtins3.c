/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:12:19 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/25 22:05:26 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_builtin_main(t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp, int status)
{
	if (pipes_head->next)
	{
		ft_freematrix(*envp);
		reset(cmds_head, pipes_head, NULL);
		exit(status);
	}
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

void	export_value(char **cmd, char ***envp)
{
	int		i;
	char	**tmp;

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
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:22:50 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:39:08 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	unset(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	i;
	int	status;

	i = -1;
	status = 0;
	if (!*cmd)
	{
		exit_status(&status);
		return ;
	}
	while (cmd[++i])
	{
		if (!check_unset(cmd[i]))
			continue ;
		*envp = env_remove(envp, cmd[i]);
	}
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

int	is_valid_identifier(char *var)
{
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var) && *var != '_')
			return (0);
		var++;
	}
	if (*var++ == '=' && var && !*var)
		return (0);
	return (1);
}

int	check_unset(char *var)
{
	int	status;

	status = 0;
	if (!is_valid_identifier(var))
	{
		ft_dprintf(2, "unset: `%s': not a valid identifier\n", var);
		status = 1;
		exit_status(&status);
		return (0);
	}
	exit_status(&status);
	return (1);
}

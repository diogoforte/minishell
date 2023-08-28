/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 21:12:19 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/28 17:48:48 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exit_builtin_main(t_redirect *cmds_head,
						t_pipe *pipes_head,
						char ***envp,
						int status)
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
	int	status;

	status = 0;
	if (!ft_isalpha(var[0]))
	{
		ft_dprintf(2, "export: `%s': not a valid identifier\n", var);
		status = 1;
		exit_status(&status);
		return (0);
	}
	while (*var && *var != '=')
	{
		if (!ft_isalnum(*var))
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
		if (!check_env(cmd[i]))
			continue ;
		tmp = ft_split(cmd[i], '=');
		if (search_env(envp, tmp[0]))
			*envp = env_remove(envp, tmp[0]);
		ft_freematrix(tmp);
		*envp = env_add(envp, cmd[i]);
	}
}

void	echo(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	flag;

	flag = 0;
	if (*cmd && ft_strncmp(*cmd, "-n", 2) == 0)
	{
		cmd++;
		flag = 1;
	}
	while (*cmd)
	{
		printf("%s", *cmd++);
		if (*cmd)
			printf(" ");
	}
	if (!flag)
		printf("\n");
	ft_freematrix(*envp);
	reset(cmds_head, pipes_head, NULL);
	exit(0);
}

int	check_max_long(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '+' || cmd[i] == '-')
		i = 1;
	while (cmd[i] == '0')
		i++;
	if (ft_strlen(&cmd[i]) < 19)
		return (1);
	if (ft_strlen(&cmd[i]) > 19)
		return (0);
	if (cmd[0] == '-')
	{
		if (ft_strncmp(&cmd[i], "9223372036854775808", ft_strlen(&cmd[i])) > 0)
			return (0);
	}
	else if (ft_strncmp(&cmd[i], "9223372036854775807", ft_strlen(&cmd[i])) > 0)
		return (0);
	return (1);
}

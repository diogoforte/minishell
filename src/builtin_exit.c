/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:21:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:26:39 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	builtin_exit(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	status;

	ft_freematrix(*envp);
	if (!cmd[1])
	{
		reset(cmds_head, pipes_head, NULL);
		exit(0);
	}
	check_digits(cmd, cmds_head, pipes_head);
	if (cmd[1] && cmd[2])
	{
		ft_dprintf(2, "minishell: exit: too many arguments\n");
		reset(cmds_head, pipes_head, NULL);
		exit(1);
	}
	else
	{
		status = ft_atoi(cmd[1]);
		reset(cmds_head, pipes_head, NULL);
		exit(status);
	}
}

void	check_digits(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head)
{
	int	j;
	int	valid;

	j = 0;
	valid = 1;
	if (!ft_isdigit(cmd[1][j]) && cmd[1][j] != '-' && cmd[1][j] != '+')
		valid = 0;
	if (cmd[1][j] == '-' || cmd[1][j] == '+')
		j++;
	while (cmd[1][j] && valid)
	{
		if (!ft_isdigit(cmd[1][j]))
			valid = 0;
		j++;
	}
	if (valid)
		valid = check_max_long(cmd[1]);
	if (!valid)
	{
		ft_dprintf(2, "minishell: exit: %s: numeric argument required\n",
			cmd[1]);
		reset(cmds_head, pipes_head, NULL);
		exit(2);
	}
}

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

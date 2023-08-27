/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/27 15:41:55 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	call_chdir(char *cmd, int *status)
{
	if (chdir(cmd))
	{
		ft_dprintf(2, "cd: %s: No such file or directory\n", cmd);
		*status = 1;
	}
	else
		*status = 0;
}

int	cd_check(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	int	status;
	int	i;

	status = 1;
	i = 0;
	while (cmd[i])
		i++;
	if (i > 1)
	{
		ft_dprintf(2, "minishell: cd: too many arguments\n");
		exit_status(&status);
		exit_builtin_main(cmds_head, pipes_head, envp, status);
		return (1);
	}
	return (0);
}

void	cd(char **cmd, t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	int			status;
	char		*current_pwd;
	static char	*old_pwd;
	char		*tmp;

	if (cd_check(cmd, cmds_head, pipes_head, envp))
		return ;
	current_pwd = getcwd(NULL, 0);
	old_pwd = search_env(envp, "OLDPWD");
	if (!*cmd || !ft_strncmp(*cmd, "~", 2))
		call_chdir((search_env(envp, "HOME")), &status);
	else if (!ft_strncmp(*cmd, "~/", 2))
	{
		tmp = ft_strjoin(search_env(envp, "HOME"), *cmd + 1);
		call_chdir(tmp, &status);
		free(tmp);
	}
	else
		call_chdir(*cmd, &status);
	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
	*envp = env_remove(envp, "OLDPWD");
	*envp = env_add(envp, old_pwd);
	free_strings(current_pwd, old_pwd);
	exit_status(&status);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

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

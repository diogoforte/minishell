/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:20:34 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 20:23:28 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

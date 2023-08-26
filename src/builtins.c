/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/25 22:51:11 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
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

void	call_chdir(char *cmd, int *status)
{
	if (chdir(cmd))
	{
		printf("Error: %s\n", strerror(errno));
		*status = 1;
	}
	else
		*status = 0;
}

void	cd(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	int			status;
	char		*current_pwd;
	static char	*old_pwd;
	char		*tmp;

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
	else if (!ft_strncmp(*cmd, "-", 2) && old_pwd)
		call_chdir(old_pwd, &status);
	else
		call_chdir(*cmd, &status);
	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
	*envp = env_remove(envp, "OLDPWD");
	*envp = env_add(envp, old_pwd);
	free_strings(current_pwd, old_pwd);
	exit_status(&status);
	exit_builtin_main(cmds_head, pipes_head, envp, status);
}

void	builtin_exit(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
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
		printf("minishell: exit: too many arguments\n");
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

	j = 0;
	while (cmd[1][j])
	{
		if (!ft_isdigit(cmd[1][j]))
		{
			printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
			reset(cmds_head, pipes_head, NULL);
			exit(2);
		}
		j++;
	}
}

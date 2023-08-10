/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/11 00:26:39 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	echo(char **cmd)
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
	exit(0);
}

void	cd(char **cmd, char ***envp)
{
	int			status;
	char		*current_pwd;
	static char	*old_pwd;

	status = 0;
	current_pwd = getcwd(NULL, 0);
	old_pwd = search_env(envp, "OLDPWD");
	if (!*cmd || !ft_strncmp(*cmd, "~", 2))
		chdir(search_env(envp, "HOME"));
	else if (!ft_strncmp(*cmd, "-", 2) && old_pwd)
		chdir(old_pwd);
	else if (chdir(*cmd))
	{
		printf("Error: %s\n", strerror(errno));
		status = 1;
	}
	old_pwd = ft_strjoin("OLDPWD=", current_pwd);
	*envp = env_remove(envp, "OLDPWD");
	*envp = env_add(envp, old_pwd);
	free(current_pwd);
	free(old_pwd);
	exit_status(&status);
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
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (!*cmd)
	{
		while ((*envp)[i])
			printf("export %s\n", (*envp)[i++]);
		exit_status(&status);
	}
	*envp = env_add(envp, *cmd);
	exit_status(&status);
}

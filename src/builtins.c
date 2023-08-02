/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:41:10 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 09:15:30 by dinunes-         ###   ########.fr       */
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
	printf("\n");
	if (!flag)
		printf("\n");
}

void	cd(char **cmd)
{
	if (!cmd)
		printf("Error: %s\n", strerror(errno));
	else if (chdir(*cmd))
		printf("Error: %s\n", strerror(errno));
}

void	pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		printf("Error: %s\n", strerror(errno));
	else
	{
		printf("%s", pwd);
		printf("\n");
		free(pwd);
	}
}

void	env(char ***envp)
{
	int	i;

	i = 0;
	while ((*envp)[i])
		printf("%s\n", (*envp)[i++]);
}

void	export(char **cmd, char ***envp)
{
	int	i;

	i = 0;
	if (!*cmd)
	{
		while ((*envp)[i])
			printf("export %s\n", (*envp)[i++]);
		return ;
	}
	*envp = env_add(envp, *cmd);
}

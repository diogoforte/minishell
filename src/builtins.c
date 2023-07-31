/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:41:10 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 08:11:36 by dinunes-         ###   ########.fr       */
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
		printf(pwd);
		printf("\n");
		free(pwd);
	}
}

void	export(char **cmd)
{
	char	**env;
	char	*value;
	char	**split;

	env = environ;
	if (!*cmd)
	{
		while (*env)
			printf("export %s\n", *env++);
		return ;
	}
	while (*cmd)
	{
		split = splitonce(*cmd++, '=');
		if (split[1] == NULL)
			value = "";
		else
			value = split[1];
		setenv(split[0], value, 1);
		if (split)
		{
			free(split);
			split = NULL;
		}
	}
}

void	env(char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
}

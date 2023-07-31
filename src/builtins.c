/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:41:10 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 06:07:29 by dinunes-         ###   ########.fr       */
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
	char	*var;
	char	*value;
	char	*name;

	env = environ;
	if (!*cmd)
	{
		while (*env)
			printf("export %s\n", *env++);
		return ;
	}
	while (*cmd)
	{
		var = *cmd;
		value = "";
		if (ft_strchr(var, '=') != NULL)
		{
			name = strtok(var, "=");
			value = strtok(NULL, "=");
			var = name;
		}
		setenv(var, value, 1);
		cmd++;
	}
}

void	env(char **envp)
{
	while (*envp)
		printf("%s\n", *envp++);
}

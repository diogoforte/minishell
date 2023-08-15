/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 21:28:39 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/13 22:04:16 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

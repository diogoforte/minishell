/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:15 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 06:08:46 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(char *line, char **envp)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = ft_split(line, ' ');
	while (cmd[i])
	{
		if (builtins(cmd, envp))
			break ;
		else
		{
			execute(cmd, envp);
			break ;
		}
		i++;
	}
	return (0);
}

int	builtins(char **cmd, char **envp)
{
	if (ft_strncmp(*cmd, "echo", 4) == 0)
		echo(cmd + 1);
	else if (ft_strncmp(*cmd, "cd", 2) == 0)
		cd(cmd + 1);
	else if (ft_strncmp(*cmd, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(*cmd, "export", 6) == 0)
		export(cmd + 1);
	else if (ft_strncmp(*cmd, "unset", 5) == 0)
	{
		if (*(++cmd))
			unsetenv(*cmd);
	}
	else if (ft_strncmp(*cmd, "env", 3) == 0)
		env(envp);
	else if (ft_strncmp(*cmd, "exit", 4) == 0)
		exit(0);
	else
		return (0);
	return (1);
}

int	execute(char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(pathfinder(cmd[0], envp), cmd, envp) == -1)
			printf("Error: %s\n", strerror(errno));
	}
	else if (pid < 0)
		printf("Error: %s\n", strerror(errno));
	else
		waitpid(pid, &status, 0);
	return (0);
}

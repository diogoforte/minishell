/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:15 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 10:17:51 by dinunes-         ###   ########.fr       */
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
	free_list(cmd);
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
	char	*path;

	pid = fork();
	if (pid == 0)
	{
		path = pathfinder(cmd[0], envp);
		if (path == NULL)
		{
			printf("Command not found: %s\n", cmd[0]);
			exit(0);
		}
		if (execve(path, cmd, envp) == -1)
		{
			printf("Error: %s\n", strerror(errno));
			free(path);
			exit(0);
		}
	}
	else
		waitpid(pid, &status, 0);
	printf("\n");
	return (0);
}

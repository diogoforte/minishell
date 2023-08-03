/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 10:32:20 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute(char **cmd, char ***envp)
{
	pid_t	pid;
	int		status;

	status = -1;
	pid = fork();
	if (!pid)
	{
		handle_input_redirection();
		handle_output_redirection();
		if ((!ft_strncmp(*cmd, "echo", 5)) || (!ft_strncmp(*cmd, "cd", 3))
			|| (!ft_strncmp(*cmd, "pwd", 4)) || (!ft_strncmp(*cmd, "export", 7))
			|| (!ft_strncmp(*cmd, "unset", 6)) || (!ft_strncmp(*cmd, "env", 4))
			|| (!ft_strncmp(*cmd, "exit", 5)))
			execute_builtin(cmd, envp);
		else
			execute_command(cmd, envp);
	}
	handle_exit_status(&status, envp);
}

void	execute_builtin(char **cmd, char ***envp)
{
	if (!ft_strncmp(*cmd, "echo", 5))
		echo(cmd + 1);
	else if (!ft_strncmp(*cmd, "cd", 3))
		cd(cmd + 1);
	else if (!ft_strncmp(*cmd, "pwd", 4))
		pwd();
	else if (!ft_strncmp(*cmd, "export", 7))
		export(cmd + 1, envp);
	else if (!ft_strncmp(*cmd, "unset", 6))
	{
		if (*(++cmd))
			env_remove(envp, *cmd);
	}
	else if (!ft_strncmp(*cmd, "env", 4))
		env(envp);
	printf("Command not found: %s\n", *cmd);
}

char	*execute_command(char **cmd, char ***envp)
{
	char	*path;

	path = pathfinder(cmd[0], envp);
	if (path == NULL)
	{
		printf("Command not found: %s\n", *cmd);
		exit(0);
	}
	if (execve(path, cmd, *envp) == -1)
	{
		printf("Error: %s\n", strerror(errno));
		free(path);
		exit(EXIT_FAILURE);
	}
	return (path);
}

void	handle_exit_status(int *status, char ***envp)
{
	char	*statusstr;
	char	*final;

	waitpid(-1, status, 0);
	if (WIFEXITED(*status))
	{
		*status = WEXITSTATUS(*status);
		statusstr = ft_itoa(*status);
		final = ft_strjoin("?=", statusstr);
		exit_status(status);
		*envp = env_remove(envp, "?");
		*envp = env_add(envp, final);
		free(statusstr);
		free(final);
	}
	printf("\n");
}

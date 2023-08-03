/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 17:32:33 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(char ***cmds, char ***envp)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (cmds[i])
	{
		pid = fork();
		if (!pid)
		{
			dup2(get_pipe()->infile, 0);
			if (cmds[i + 1])
				dup2(get_pipe()->pipe[1], 1);
			close(get_pipe()->pipe[0]);
			execute(cmds[i], envp);
			exit(EXIT_FAILURE);
		}
		else
		{
			waitpid(pid, NULL, 0);
			close(get_pipe()->pipe[1]);
			get_pipe()->infile = get_pipe()->pipe[0];
			i++;
		}
	}
}

void	execute(char **cmd, char ***envp)
{
	pid_t	pid;
	int		status;

	status = -1;
	if (execute_builtin_main(cmd, envp))
		return ;
	else
	{
		pid = fork();
		if (!pid)
		{
			handle_input_redirection();
			handle_output_redirection();
			if ((!ft_strncmp(*cmd, "echo", 5)) || (!ft_strncmp(*cmd, "pwd", 4))
				|| (!ft_strncmp(*cmd, "env", 4)) || (!ft_strncmp(*cmd, "exit",
						5)))
				execute_builtin(cmd, envp);
			else
				execute_command(cmd, envp);
		}
		handle_exit_status(&status, envp);
	}
}

int	execute_builtin_main(char **cmd, char ***envp)
{
	int	status;

	status = 0;
	if (!ft_strncmp(*cmd, "cd", 3))
		cd(cmd + 1);
	else if (!ft_strncmp(*cmd, "export", 7))
		export(cmd + 1, envp);
	else if (!ft_strncmp(*cmd, "unset", 6))
	{
		if (*(++cmd))
		{
			env_remove(envp, *cmd);
		}
		exit_status(&status);
	}
	else if (!ft_strncmp(*cmd, "exit", 4))
		exit(0);
	else
		return (0);
	return (1);
}

void	execute_builtin(char **cmd, char ***envp)
{
	if (!ft_strncmp(*cmd, "echo", 5))
		echo(cmd + 1);
	else if (!ft_strncmp(*cmd, "pwd", 4))
		pwd();
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

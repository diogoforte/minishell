/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/13 21:26:26 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(char ***cmds, char ***envp)
{
	pid_t	pid;
	int		status;
	int		index;

	index = 0;
	while (cmds[index])
	{
		if (!execute_builtin_main(cmds[index], envp))
		{
			pid = fork();
			if (!pid)
				handle_child(cmds, index, envp);
			handle_parent(index);
		}
		index++;
	}
	handle_exit_status(&status, envp);
}

void	execute(char **cmd, char ***envp)
{
	if (get_redirections()->command
		&& !ft_strncmp(get_redirections()->command, *cmd, ft_strlen(*cmd)))
		handle_output_redirection();
	handle_input_redirection();
	if (*cmd && ((!ft_strncmp(*cmd, "echo", 5)) || (!ft_strncmp(*cmd, "pwd", 4))
			|| (!ft_strncmp(*cmd, "env", 4)) || (!ft_strncmp(*cmd, "exit", 5))))
		execute_builtin(cmd, envp);
	else
		execute_command(cmd, envp);
}

int	execute_builtin_main(char **cmd, char ***envp)
{
	int	status;

	status = 1;
	if (*cmd && !ft_strncmp(*cmd, "cd", 3))
		cd(cmd + 1, envp);
	else if (*cmd && !ft_strncmp(*cmd, "export", 7))
		export(cmd + 1, envp);
	else if (*cmd && !ft_strncmp(*cmd, "unset", 6))
	{
		if (*(++cmd))
		{
			*envp = env_remove(envp, *cmd);
			status = 0;
		}
		exit_status(&status);
	}
	else if (*cmd && !ft_strncmp(*cmd, "exit", 4))
	{
		if (*(++cmd) && !*(cmd + 1))
			exit(ft_atoi(*cmd));
		exit(0);
	}
	else
		return (0);
	return (1);
}

void	execute_builtin(char **cmd, char ***envp)
{
	if (*cmd && !ft_strncmp(*cmd, "echo", 5))
		echo(cmd + 1);
	else if (*cmd && !ft_strncmp(*cmd, "pwd", 4))
		pwd();
	else if (*cmd && !ft_strncmp(*cmd, "env", 4))
		env(envp);
	printf("Command not found: %s\n", *cmd);
}

void	execute_command(char **cmd, char ***envp)
{
	char	*path;

	path = pathfinder(cmd[0], envp);
	if (!*cmd)
		return ;
	if (!path)
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
}

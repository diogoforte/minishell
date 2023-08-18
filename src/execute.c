/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 16:36:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_redirect *cmds_head, char ***envp)
{
	pid_t		pid;
	int			status;
	t_redirect	*current;
	int			index;

	current = cmds_head;
	index = 0;
	while (current)
	{
		if (current->cmd && !execute_builtin_main(current->cmd, envp))
		{
			pid = fork();
			if (!pid)
				handle_child(current, index, envp);
			handle_parent(current, index);
		}
		index++;
		current = current->next;
	}
	handle_exit_status(&status);
}

void	execute(t_redirect *current_cmd, char ***envp)
{
	handle_output_redirection(current_cmd);
	handle_input_redirection(current_cmd);
	if (current_cmd->cmd[0] && (!ft_strncmp(current_cmd->cmd[0], "echo", 5)
			|| !ft_strncmp(current_cmd->cmd[0], "pwd", 4)
			|| !ft_strncmp(current_cmd->cmd[0], "env", 4)
			|| !ft_strncmp(current_cmd->cmd[0], "exit", 5)))
		execute_builtin(current_cmd->cmd, envp);
	else
		execute_command(current_cmd->cmd, envp);
}

int	execute_builtin_main(char **cmd, char ***envp)
{
	if (*cmd && !ft_strncmp(*cmd, "cd", 3))
		cd(cmd + 1, envp);
	else if (*cmd && !ft_strncmp(*cmd, "export", 7))
		export(cmd + 1, envp);
	else if (*cmd && !ft_strncmp(*cmd, "unset", 6))
		unset(cmd + 1, envp);
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

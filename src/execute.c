/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/21 12:32:22 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	pid_t		pid;
	t_redirect	*current;
	int			status;
	int			index;

	current = cmds_head;
	index = 0;
	pipe(pipes_head->pipe);
	while (current && current->cmd)
	{
		if (!index && !current->next && execute_builtin_main(current,
				envp) == 0)
			break ;
		else
		{
			pid = fork();
			if (!pid)
				handle_child(current, pipes_head, index, envp);
			handle_parent(current, pipes_head, index);
		}
		index++;
		current = current->next;
	}
	handle_exit_status(&status);
}

void	execute(t_redirect *current_cmd, char ***envp)
{
	if (current_cmd->out_redir)
	{
		dup2(current_cmd->out_fd, STDOUT_FILENO);
		close(current_cmd->out_fd);
	}
	if (current_cmd->in_redir)
	{
		dup2(current_cmd->in_fd, STDIN_FILENO);
		close(current_cmd->in_fd);
	}
	if (!execute_builtin(current_cmd->cmd, envp))
		execute_command(current_cmd->cmd, envp);
}

int	execute_builtin_main(t_redirect *current_cmd, char ***envp)
{
	if (*current_cmd->cmd)
	{
		if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "cd", 3))
			cd(current_cmd->cmd + 1, envp);
		else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "export",
				7))
			export(current_cmd->cmd + 1, envp);
		else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "unset",
				6))
			unset(current_cmd->cmd + 1, envp);
		else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "exit", 5))
			builtin_exit(current_cmd->cmd);
		else
			return (1);
		return (0);
	}
	return (1);
}

int	execute_builtin(char **cmd, char ***envp)
{
	if (*cmd && !ft_strncmp(*cmd, "echo", 5))
		echo(cmd + 1);
	else if (*cmd && !ft_strncmp(*cmd, "pwd", 4))
		pwd();
	else if (*cmd && !ft_strncmp(*cmd, "env", 4))
		env(envp);
	return (0);
}

void	execute_command(char **cmd, char ***envp)
{
	char	*path;

	path = pathfinder(cmd[0], envp);
	if (!*cmd)
		return ;
	if (*cmd && (!ft_strncmp(*cmd, "cd", 3) || !ft_strncmp(*cmd, "export", 7)
			|| !ft_strncmp(*cmd, "unset", 6) || !ft_strncmp(*cmd, "exit", 5)))
		return ;
	if (!path)
	{
		printf("Command not found: %s\n", *cmd);
		exit(127);
	}
	if (execve(path, cmd, *envp) == -1)
	{
		printf("Error: %s\n", strerror(errno));
		free(path);
		exit(EXIT_FAILURE);
	}
}

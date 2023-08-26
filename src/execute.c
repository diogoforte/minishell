/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 07:13:58 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/26 22:38:00 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_pipeline(t_redirect *cmds_head, t_pipe *pipes_head,
		char ***envp)
{
	pid_t		pid;
	t_redirect	*heads[2];
	int			status;
	int			index;

	heads[0] = cmds_head;
	heads[1] = cmds_head;
	index = 0;
	pipe(pipes_head->pipe);
	while (heads[0] && heads[0]->cmd)
	{
		if (!index && !heads[0]->next && execute_builtin_main(heads[0],
				cmds_head, pipes_head, envp) == 0)
			break ;
		pid = fork();
		if (!pid)
			handle_child(heads, pipes_head, index, envp);
		handle_parent(heads[0], pipes_head, index);
		index++;
		heads[0] = heads[0]->next;
	}
	handle_exit_status(&status);
}

void	execute(t_redirect *current_cmd, t_redirect *cmds_head,
		t_pipe *pipes_head, char ***envp)
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
	if (!execute_builtin(current_cmd->cmd, cmds_head, pipes_head, envp)
		&& execute_builtin_main(current_cmd, cmds_head, pipes_head, envp))
		execute_command(current_cmd->cmd, cmds_head, pipes_head, envp);
}

int	execute_builtin_main(t_redirect *current_cmd,
		t_redirect *cmds_head, t_pipe *pipes_head, char ***envp)
{
	int status;

	status = 1;
	if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "cd", 3))
	{
		cd(current_cmd->cmd + 1, cmds_head, pipes_head, envp);
	}
	else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "export",
			7))
		export(current_cmd->cmd + 1, cmds_head, pipes_head, envp);
	else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "unset",
			6))
		unset(current_cmd->cmd + 1, cmds_head, pipes_head, envp);
	else if (*current_cmd->cmd && !ft_strncmp(*current_cmd->cmd, "exit", 5))
		builtin_exit(current_cmd->cmd, cmds_head, pipes_head, envp);
	else
		return (1);
	return (0);
}

int	execute_builtin(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	if (*cmd && !ft_strncmp(*cmd, "echo", 5))
		echo(cmd + 1, cmds_head, pipes_head, envp);
	else if (*cmd && !ft_strncmp(*cmd, "pwd", 4))
		pwd(cmds_head, pipes_head, envp);
	else if (*cmd && !ft_strncmp(*cmd, "env", 4))
		env(cmds_head, pipes_head, envp);
	return (0);
}

void	execute_command(char **cmd, t_redirect *cmds_head,
			t_pipe *pipes_head, char ***envp)
{
	char	*path;

	path = pathfinder(cmd[0], envp);
	if (!path || !**cmd)
	{
		printf("Command not found: %s\n", *cmd);
		ft_freematrix(*envp);
		reset(cmds_head, pipes_head, NULL);
		exit(127);
	}
	if (execve(path, cmd, *envp) == -1)
	{
		printf("Error: %s\n", strerror(errno));
		free(path);
		exit(126);
	}
}

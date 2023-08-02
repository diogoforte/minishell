/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/27 19:10:15 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 04:26:16 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	parsing(char *line, char ***envp)
{
	char	**cmd;
	int		i;

	i = 0;
	cmd = parse_cmd(line);
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

int	builtins(char **cmd, char ***envp)
{
	if (ft_strncmp(*cmd, "echo", 4) == 0)
		echo(cmd + 1);
	else if (ft_strncmp(*cmd, "cd", 2) == 0)
		cd(cmd + 1);
	else if (ft_strncmp(*cmd, "pwd", 3) == 0)
		pwd();
	else if (ft_strncmp(*cmd, "export", 6) == 0)
		export(cmd + 1, envp);
	else if (ft_strncmp(*cmd, "unset", 5) == 0)
	{
		if (*(++cmd))
			env_remove(envp, *cmd);
	}
	else if (ft_strncmp(*cmd, "env", 3) == 0)
		env(envp);
	else if (ft_strncmp(*cmd, "exit", 4) == 0)
		exit(0);
	else
		return (0);
	return (1);
}

int	execute(char **cmd, char ***envp)
{
	pid_t	pid;
	int		status;
	char	*path;
	int		in_fd;
	int		out_fd;

	in_fd = -1;
	out_fd = -1;
	pid = fork();
	if (pid == 0)
	{
		if (get_redirections()->in_redir == 2 && get_redirections()->heredoc)
		{
			in_fd = open("/tmp/heredoc_file", O_RDONLY);
			if (in_fd < 0)
				perror("Error opening heredoc file");
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		else if (get_redirections()->in_redir && get_redirections()->in_file)
		{
			in_fd = open(get_redirections()->in_file, O_RDONLY);
			if (in_fd < 0)
				perror("Error opening input file");
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (get_redirections()->out_redir && get_redirections()->out_file)
		{
			if (get_redirections()->out_redir == 1)
				out_fd = open(get_redirections()->out_file,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (get_redirections()->out_redir == 2)
				out_fd = open(get_redirections()->out_file,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (out_fd < 0)
				perror("Error opening output file");
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		path = pathfinder(cmd[0], envp);
		if (path == NULL)
		{
			printf("Command not found: %s\n", cmd[0]);
			exit(0);
		}
		if (execve(path, cmd, *envp) == -1)
		{
			printf("Error: %s\n", strerror(errno));
			free(path);
			exit(0);
		}
	}
	else
		waitpid(pid, &status, 0);
	if (get_redirections()->in_file)
	{
		free(get_redirections()->in_file);
		get_redirections()->in_file = NULL;
	}
	if (get_redirections()->out_file)
	{
		free(get_redirections()->out_file);
		get_redirections()->out_file = NULL;
	}
	get_redirections()->in_redir = 0;
	get_redirections()->out_redir = 0;
	get_redirections()->heredoc = 0;
	printf("\n");
	return (0);
}

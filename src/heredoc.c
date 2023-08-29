/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 09:42:15 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc_file(char *str, char ***envp)
{
	t_heredoc	heredoc;
	int			i;

	heredoc.fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (heredoc.fd == -1)
		return (0);
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	heredoc.str = str;
	heredoc.envp = envp;
	heredoc.start = i;
	heredoc.end = ft_strlen(str);
	heredoc.delimiter = ft_substr(str, 0, heredoc.start);
	while (heredoc.str[heredoc.start] && heredoc.str[heredoc.start] != '\n')
		heredoc.start++;
	if (ft_strnstr(str + heredoc.start, heredoc.delimiter, heredoc.end
			- heredoc.start))
		write_all_to_file(&heredoc);
	else
		write_to_file(&heredoc);
	free(heredoc.delimiter);
	close(heredoc.fd);
	return (1);
}

void	write_all_to_file(t_heredoc *heredoc)
{
	char	*current;
	char	*content_current;
	char	*processed_line;
	char	*tmp;
	size_t	content_length;

	content_current = heredoc->str + heredoc->start + 1;
	current = ft_strchr(content_current, '\n');
	while (current)
	{
		content_length = current - content_current;
		processed_line = ft_substr(content_current, 0, content_length);
		tmp = assign_variable(processed_line, heredoc->envp, 0);
		tmp = strip_quotes(tmp);
		if (!ft_strncmp(tmp, heredoc->delimiter, content_length)
			&& content_length == ft_strlen(heredoc->delimiter))
			break ;
		write(heredoc->fd, tmp, ft_strlen(tmp));
		write(heredoc->fd, "\n", 1);
		content_current = current + 1;
		free(processed_line);
		current = ft_strchr(content_current, '\n');
	}
}

void	free_heredoc(t_heredoc *heredoc)
{
	free(heredoc->str);
	free(heredoc->delimiter);
	close(heredoc->fd);
	ft_freematrix(*heredoc->envp);
	exit (1);
}

void	process_heredoc_lines(t_heredoc *heredoc)
{
	char	*processed_line;

	while (1)
	{
		heredoc->str = readline("> ");
		if (!heredoc->str || (!ft_strncmp(heredoc->delimiter, "\"\"", 2)
				&& !*heredoc->str))
			free_heredoc(heredoc);
		processed_line = assign_variable(heredoc->str, heredoc->envp, 0);
		processed_line = strip_quotes(processed_line);
		if (processed_line != heredoc->str)
			heredoc->str = processed_line;
		if (ft_strlen(heredoc->str) == ft_strlen(heredoc->delimiter)
			&& !ft_strncmp(heredoc->str, heredoc->delimiter,
				ft_strlen(heredoc->delimiter)))
			free_heredoc(heredoc);
		write(heredoc->fd, heredoc->str, ft_strlen(heredoc->str));
		write(heredoc->fd, "\n", 1);
		free(heredoc->str);
	}
}

void	write_to_file(t_heredoc *heredoc)
{
	int	pid;
	int	status;
	int	fd;

	signals(3);
	pid = fork();
	if (!pid)
	{
		signals(2);
		process_heredoc_lines(heredoc);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
	{
		fd = open("/tmp/heredoc_file", O_TRUNC);
		write(fd, "", 1);
		close(fd);
	}
	signals(0);
}

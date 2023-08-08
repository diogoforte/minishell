/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/08 22:26:34 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc_file(char *str, char ***envp)
{
	t_heredoc	heredoc;
	int			i;
	char		*delimiter;

	if (!*str)
		return (0);
	heredoc.fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (heredoc.fd == -1)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	heredoc.str = str;
	heredoc.envp = envp;
	heredoc.start = i;
	heredoc.end = ft_strlen(str);
	delimiter = ft_substr(heredoc.str, 0, heredoc.start);
	if (ft_strnstr(str + heredoc.start, delimiter, heredoc.end - heredoc.start))
		write_all_to_file(&heredoc);
	else
		write_to_file(&heredoc);
	free(delimiter);
	close(heredoc.fd);
	return (1);
}

void	write_all_to_file(t_heredoc *heredoc)
{
	char	*delimiter;
	char	*content_start;
	char	*content_end;
	char	*processed_line;

	delimiter = ft_substr(heredoc->str, 0, heredoc->start);
	content_start = heredoc->str + heredoc->start + 1;
	processed_line = assign_variable(content_start, heredoc->envp, 0);
	content_end = ft_strnstr(processed_line, delimiter, heredoc->end
			- (content_start - processed_line));
	*content_end = '\0';
	if (content_end && (!content_end[ft_strlen(delimiter)]
			|| content_end[ft_strlen(delimiter)] == '\n'))
		write(heredoc->fd, processed_line, ft_strlen(processed_line));
	free(delimiter);
	if (processed_line != content_start)
		free(processed_line);
}

void	write_to_file(t_heredoc *heredoc)
{
	char	*delimiter;
	char	*line;
	char	*processed_line;

	delimiter = ft_substr(heredoc->str, 0, heredoc->start);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		processed_line = assign_variable(line, heredoc->envp, 0);
		if (processed_line != line)
			line = processed_line;
		if (ft_strlen(line) == ft_strlen(delimiter) && !ft_strncmp(line,
				delimiter, ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(heredoc->fd, line, ft_strlen(line));
		write(heredoc->fd, "\n", 1);
		free(line);
	}
	free(delimiter);
}

int	find_delimiter(char *line)
{
	int	i;

	i = 0;
	while (line[i + 1])
		i++;
	while (line[i - 1] && line[i - 1] != '\n')
		i--;
	return (i);
}

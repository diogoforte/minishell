/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 22:09:52 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

#define DELIMITER 0
#define NL 1

void	free_strings(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

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
	char	*spechr[2];
	char	*content_current;
	char	*processed_line;
	char	*tmp;
	size_t	content_length;

	spechr[DELIMITER] = ft_substr(heredoc->str, 0, heredoc->start);
	content_current = heredoc->str + heredoc->start + 1;
	spechr[NL] = ft_strchr(content_current, '\n');
	while (spechr[NL])
	{
		content_length = spechr[NL] - content_current;
		processed_line = ft_substr(content_current, 0, content_length);
		tmp = assign_variable(processed_line, heredoc->envp, 0);
		strip_quotes(tmp);
		if (!ft_strncmp(tmp, spechr[DELIMITER], content_length)
			&& content_length == ft_strlen(spechr[DELIMITER]))
			break ;
		write(heredoc->fd, tmp, ft_strlen(tmp));
		write(heredoc->fd, "\n", 1);
		content_current = spechr[NL] + 1;
		free(processed_line);
		spechr[NL] = ft_strchr(content_current, '\n');
	}
	free(spechr[DELIMITER]);
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
		strip_quotes(processed_line);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/08 14:57:06 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc_file(char *str, char ***envp)
{
	t_heredoc	params;
	int			i;
	char		*delimiter;

	params.fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (params.fd == -1)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	params.str = str;
	params.envp = envp;
	params.start = i;
	params.end = ft_strlen(str);
	delimiter = ft_substr(params.str, 0, params.start);
	if (ft_strnstr(str + params.start, delimiter, params.end - params.start))
		write_all_to_file(&params);
	else
		write_to_file(&params);
	free(delimiter);
	close(params.fd);
	return (1);
}

void	write_all_to_file(t_heredoc *params)
{
	char	*delimiter;
	char	*content_start;
	char	*content_end;

	delimiter = ft_substr(params->str, 0, params->start);
	content_start = params->str + params->start + 1;
	content_end = ft_strnstr(content_start, delimiter, params->end
			- (content_start - params->str));
	if (content_end && (!content_end[ft_strlen(delimiter)]
			|| content_end[ft_strlen(delimiter)] == '\n'))
	{
		*content_end = 0;
		write(params->fd, content_start, ft_strlen(content_start));
	}
	free(delimiter);
}

void	write_to_file(t_heredoc *params)
{
	char	*delimiter;
	char	*line;

	delimiter = ft_substr(params->str, 0, params->start);
	line = NULL;
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			break ;
		if (strlen(line) == strlen(delimiter) && !ft_strncmp(line, delimiter,
				ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(params->fd, line, ft_strlen(line));
		write(params->fd, "\n", 1);
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

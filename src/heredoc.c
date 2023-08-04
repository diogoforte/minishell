/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/04 09:22:21 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc_file(char *str, char ***envp)
{
	t_heredoc	params;
	int			fd;
	int			i;
	int			j;

	params.fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	while (str[j])
		j++;
	j--;
	while (j >= 0 && str[j] != '\n')
		j--;
	j++;
	params.str = str;
	params.envp = envp;
	params.start = i;
	params.end = j;
	write_to_file(&params);
	close(params.fd);
	return (1);
}

int	write_to_file(t_heredoc *params)
{
	char	*delimiter1;
	char	*delimiter2;
	char	*final;

	delimiter1 = ft_substr(params->str, 0, params->start);
	delimiter2 = ft_substr(params->str, params->end, ft_strlen(params->str)
			- params->end);
	if (!ft_strncmp(delimiter1, delimiter2, ft_strlen(delimiter1)))
	{
		final = assign_variable(ft_substr(params->str, params->start + 1,
					params->end - params->start - 2), params->envp);
		write(params->fd, final, ft_strlen(final));
		free(final);
	}
	free(delimiter1);
	free(delimiter2);
	return (1);
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

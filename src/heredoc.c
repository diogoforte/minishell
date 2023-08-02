/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/02 04:26:59 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	create_heredoc_file(char *str)
{
	int		fd;
	int		i;
	int		j;
	char	*delimiter1;
	char	*delimiter2;
	char	*final;

	fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (0);
	i = 0;
	j = 0;
	delimiter1 = NULL;
	delimiter2 = NULL;
	while (str[i] && str[i] != '\n')
		i++;
	delimiter1 = ft_substr(str, 0, i);
	while (str[j])
		j++;
	j--;
	while (j >= 0 && str[j] != '\n')
		j--;
	j++;
	delimiter2 = ft_substr(str, j, ft_strlen(str) - j);
	if (!ft_strncmp(delimiter1, delimiter2, ft_strlen(delimiter1)))
	{
		final = assign_variable(ft_substr(str, i + 1, j - i - 2));
		write(fd, final, ft_strlen(final));
	}
	free(delimiter1);
	free(delimiter2);
	free(final);
	close(fd);
	return (1);
}

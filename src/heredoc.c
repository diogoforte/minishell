/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 22:52:41 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 10:32:47 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	create_heredoc_file(char *str, char ***envp)
{
	int	fd;
	int	i;
	int	j;

	fd = open("/tmp/heredoc_file", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (0);
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
	write_to_file(fd, str, i, j, envp);
	close(fd);
	return (1);
}

int	write_to_file(int fd, char *str, int start, int end, char ***envp)
{
	char	*delimiter1;
	char	*delimiter2;
	char	*final;

	delimiter1 = ft_substr(str, 0, start);
	delimiter2 = ft_substr(str, end, ft_strlen(str) - end);
	if (!ft_strncmp(delimiter1, delimiter2, ft_strlen(delimiter1)))
	{
		final = assign_variable(ft_substr(str, start + 1, end - start - 2),
				envp);
		write(fd, final, ft_strlen(final));
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



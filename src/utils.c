/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 11:41:10 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_list(char **list)
{
	int	i;

	if (list)
	{
		i = 0;
		while (list[i])
			free(list[i++]);
		free(list);
	}
}

char	**splitonce(char *str, const char delim)
{
	char	**result;
	char	*delimpos;

	result = (char **)malloc(2 * sizeof(char *));
	if (!result)
		return (NULL);
	delimpos = ft_strchr(str, delim);
	if (delimpos)
	{
		*delimpos = '\0';
		result[0] = str;
		result[1] = delimpos + 1;
	}
	else
	{
		result[0] = str;
		result[1] = NULL;
	}
	return (result);
}

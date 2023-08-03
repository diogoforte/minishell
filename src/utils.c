/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 07:14:30 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 05:16:51 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

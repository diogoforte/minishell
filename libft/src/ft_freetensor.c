/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetensor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 15:02:09 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 16:46:37 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdlib.h>

void	ft_freetensor(char ***tensor)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (tensor)
	{
		while (tensor[i] != NULL)
		{
			j = 0;
			while (tensor[i][j] != NULL)
			{
				free(tensor[i][j]);
				j++;
			}
			free(tensor[i]);
			i++;
		}
		free(tensor);
	}
}

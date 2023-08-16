/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freematrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 05:15:24 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 23:57:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_freematrix(char **matrix)
{
	int	i;

	if (matrix)
	{
		i = 0;
		while (matrix[i])
			free(matrix[i++]);
		free(matrix);
	}
}

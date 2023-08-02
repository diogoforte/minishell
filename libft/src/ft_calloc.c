/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:10:40 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/05 23:35:18 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Description:
	Calloc allocates memory and sets the allocated memory to zero.
Return Value:
	A pointer to the allocated memory, or NULL if the request fails.
*/

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*d;

	d = malloc(nitems * size);
	if (!d)
		return (NULL);
	ft_bzero(d, nitems * size);
	return (d);
}

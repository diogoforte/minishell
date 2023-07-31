/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 01:42:03 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:10:42 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Memset copies the character c to the first n characters of the
	string pointed to, by the argument str.
Return Value:
	Returns a pointer to the memory area str.
*/

void	*ft_memset(void *str, int c, size_t n)
{
	size_t			i;
	unsigned char	*a;

	a = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		a[i] = c;
		i++;
	}
	return (str);
}

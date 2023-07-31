/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:19:53 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:03:00 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Memchr searches for the first occurrence of the character c
	in the first n bytes of the string pointed to, by the argument str.
Return Value:
	Returns a pointer to the matching byte or NULL if the character
	does not occur in the given memory area.
*/

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t				i;
	const unsigned char	*strcast;
	unsigned char		ch;

	i = 0;
	strcast = (const unsigned char *) str;
	ch = (unsigned char) c;
	while (i < n)
	{
		if (*(unsigned char *)(strcast + i) == ch)
			return ((unsigned char *)(str + i));
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:25:37 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:26:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Appends src to dest to at most the size of dest -1
	to ensure its NULL terminated.
Return Value:
	size of str it tried t create (len of des + src)
 	if n < size of dest n is assumed as len of dest,
	returning (n + len of  src).
*/

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	if (size == 0 || size <= i)
		return (ft_strlen((char *)src) + size);
	while (src[j] && j < (size - i - 1))
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (i + ft_strlen((char *)src));
}

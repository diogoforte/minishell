/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 07:34:43 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:31:39 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	locates the first instance of str little on str big on the
	first n bytes of big.
Return Value:
	pointer to the first instance of needle in haystack if found.
 	NULL if not found.
 	pointer to haystack if needle is empty.
*/

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	size;

	if (!len && little[0])
		return (NULL);
	i = -1;
	size = ft_strlen(little);
	if (ft_strlen(big) >= size && len >= size)
	{	
		while (++i <= len - size)
		{
			if (!ft_strncmp(&big[i], little, size))
				return ((char *)&big[i]);
		}
	}
	return (NULL);
}

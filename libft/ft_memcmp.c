/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:18:50 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:04:57 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Memcmp compares the first n bytes of memory area str1 and memory
	area str2.
Return Value:
	if Return value < 0 then it indicates str1 is less than str2.
	if Return value > 0 then it indicates str2 is less than str1.
	if Return value = 0 then it indicates str1 is equal to str2.
*/

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i)
	{
		if (((unsigned char *) str1)[i] == ((unsigned char *) str2)[i])
			i++;
		else
			return (((unsigned char *)str1)[i] - ((unsigned char *)str2)[i]);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:52:29 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:18:14 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Strchr searches for the first occurrence of the character c 
	in the string pointed to by the argument str.
Return Value:
	returns a pointer to the first occurrence of the character c
	in the string str, or NULL if the character is not found.
*/

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (unsigned char) c)
			return ((char *)str);
		str++;
	}
	if ((unsigned char) c == '\0')
		return ((char *) str);
	return (NULL);
}

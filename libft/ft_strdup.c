/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 05:27:46 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:21:22 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Strdup() function returns a pointer to a new string which is
    a duplicate of the string s.  Memory for the new string is
    allocated with malloc(3).
Return Value:
	returns a pointer to the duplicated string.
	It returns NULL if insufficient memory was available.	 
*/

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*s2;

	s2 = malloc(ft_strlen((char *) s) + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (((char *)s)[i])
	{
		s2[i] = ((char *)s)[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

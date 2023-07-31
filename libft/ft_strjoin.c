/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 08:11:50 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:23:22 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.
address to ’f’ to be modified if necessary.
Return Value:
	The new string.
	NULL if the allocation fails.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;

	res = malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!(res))
		return (NULL);
	ft_strlcpy(res, s1, ft_strlen((char *)s1) + 1);
	ft_strlcat(res, s2, ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	return (res);
}

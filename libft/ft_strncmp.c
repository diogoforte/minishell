/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 06:50:57 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:42:56 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	compares str1 and str2, (max n bytes).
Return Value:
	0 if strings are equal.
	(> 0) if str1 > str2 (values not size).
	(< 0) if str1 < str2 (values not size).
*/

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t	i;

	i = 0;
	while (n--)
	{
		if (str1[i] == str2[i] && str1[i] && str2[i])
			i++;
		else
			return (((unsigned char *) str1)[i] - ((unsigned char *) str2)[i]);
	}
	return (0);
}

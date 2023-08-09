/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:45:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/09 15:54:09 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strpbrk(char *str, char *set)
{
	char	*p;
	char	*s;

	p = str;
	while (*p)
	{
		s = set;
		while (*s)
		{
			if (*p == *s)
				return (p);
			s++;
		}
		p++;
	}
	return (NULL);
}

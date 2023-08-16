/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triplejoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 02:13:12 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 23:57:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_triplejoin(char *s1, char *s2, char *s3)
{
	char	*res;
	int		i;

	i = 0;
	if (!s1 || !s2 || !s3)
		return (NULL);
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1);
	while (*s1)
		res[i++] = *s1++;
	while (*s2)
		res[i++] = *s2++;
	while (*s3)
		res[i++] = *s3++;
	res[i] = 0;
	return (res);
}

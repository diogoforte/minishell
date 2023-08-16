/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:35:23 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 23:57:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Isdigit checks if the passed character is a digit.
Return Value:
	Returns 1 if (a) is a digit or a letter, else it returns 0.	
*/

int	ft_isdigit(int a)
{
	if (a >= '0' && a <= '9')
		return (1);
	else
		return (0);
}

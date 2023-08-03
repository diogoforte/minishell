/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 23:33:20 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 05:10:26 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

/* 
Description:
	Isalnum checks if the passed character is alphanumeric.
Return Value:
	Returns 1 if (a) is a digit or a letter, else it returns 0.	
*/

int	ft_isalnum(int a)
{
	if (ft_isalpha(a))
		return (1);
	if (ft_isdigit(a))
		return (1);
	else
		return (0);
}

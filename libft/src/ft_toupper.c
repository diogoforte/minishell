/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:33:45 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/16 23:57:35 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	passes given char to uppercase if is lowerrcase
Return Value:
	uppercase ch if lowercase, ch if not.
*/

int	ft_toupper(int ch)
{
	if (ch >= 'a' && ch <= 'z')
		ch -= 32;
	return (ch);
}

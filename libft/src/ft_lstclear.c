/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 12:22:06 by dinunes-          #+#    #+#             */
/*   Updated: 2022/11/06 06:38:26 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
Description:
	Deletes and frees the given node and every
	successor of that node, using the function ’del’ and free(3).
	Finally, the pointer to the list must be set to NULL
Return Value:
	None.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*d;

	while (*lst)
	{
		d = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = d;
	}
	*lst = NULL;
}

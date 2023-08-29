/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:24:16 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 18:01:32 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint3(int sig)
{
	int	i;

	(void) sig;
	write(1, "\n", 1);
	i = 3;
	while (i < 1024)
		close(i++);
	exit(130);
}

void	handle_sigquit3(int sig)
{
	(void) sig;
}

void	handle_sigint4(int sig)
{
	(void) sig;
}

void	handle_sigquit4(int sig)
{
	(void) sig;
}

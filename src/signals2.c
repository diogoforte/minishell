/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/28 21:24:16 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 19:54:01 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	handle_sigint3(int sig)
{
	int	i;

	(void)sig;
	i = 3;
	while (i < FOPEN_MAX)
		close(i++);
	write(1, "\n", 1);
	exit(130);
}

void	handle_sigquit3(int sig)
{
	(void)sig;
}

void	handle_sigint4(int sig)
{
	(void)sig;
}

void	handle_sigquit4(int sig)
{
	(void)sig;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:01:51 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/29 06:47:34 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signals(int n)
{
	if (n == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
	}
	if (n == 1)
	{
		signal(SIGINT, handle_sigint2);
		signal(SIGQUIT, handle_sigquit2);
	}
	if (n == 2)
	{
		signal(SIGINT, handle_sigint3);
		signal(SIGQUIT, handle_sigquit3);
	}
	if (n == 3)
	{
		signal(SIGINT, handle_sigint4);
		signal(SIGQUIT, handle_sigquit4);
	}
}

void	handle_sigint2(int sig)
{
	int	exit;

	(void)sig;
	exit = 130;
	exit_status(&exit);
}

void	handle_sigquit2(int sig)
{
	int	exit;

	(void)sig;
	exit = 131;
	exit_status(&exit);
	printf("Quit\n");
}

void	handle_sigint(int sig)
{
	int	exit;

	(void)sig;
	exit = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	exit_status(&exit);
}

void	handle_sigquit(int sig)
{
	(void)sig;
	rl_redisplay();
}

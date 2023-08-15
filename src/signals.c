/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 09:01:51 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/15 15:45:33 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	signals(int n)
{
	if (n == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		return ;
	}
	signal(SIGINT, handle_sigint2);
	signal(SIGQUIT, handle_sigquit2);
}

void	handle_sigint2(int sig)
{
	(void)sig;
}

void	handle_sigquit2(int sig)
{
	printf("\nquit (core dumped)");
	(void)sig;
}

void	handle_sigint(int sig)
{
	(void)sig;
	rl_redisplay();
	rl_replace_line("", 0);
	printf("\n");
	print_prompt();
}

void	handle_sigquit(int sig)
{
	rl_replace_line("", 0);
	rl_redisplay();
	(void)sig;
}

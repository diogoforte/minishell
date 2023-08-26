/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 22:09:16 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/26 22:13:08 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	validate_pipes_2(char *line, int i)
{
	if (i == 0)
		return (0);
	if (!line[i + 1] || line[i + 1] == '|')
		return (0);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (0);
	return (1);
}

int	validate_red_2(char *line, int i)
{
	char	current_redirection;

	current_redirection = line[i];
	if (i != 0 && line[i - 1] == current_redirection)
		return (0);
	if (line[i + 1] == current_redirection)
		i++;
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '>' || line[i] == '<' || !line[i])
		return (0);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 21:35:11 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end(char *start)
{
	char	*end;
	char	quote;

	end = start;
	if (*start == '"' || *start == '\'')
	{
		quote = *start;
		end++;
		while (*end && *end != quote)
			end++;
		if (*end)
			end++;
	}
	else
	{
		while (*end && *end != ' ')
			end++;
	}
	return (end);
}

char	**resize_cmd(char **cmd, int count)
{
	char	**new_cmd;

	new_cmd = malloc((count + 2) * sizeof(char *));
	if (cmd != NULL)
	{
		ft_memcpy(new_cmd, cmd, count * sizeof(char *));
		free(cmd);
	}
	return (new_cmd);
}

void	strip_quotes(char *arg)
{
	int	arg_len;

	arg_len = ft_strlen(arg);
	if (arg[0] == '"' || arg[0] == '\'')
	{
		ft_memmove(arg, arg + 1, arg_len - 1);
		arg[arg_len - 2] = '\0';
	}
}

char	**parse_cmd(char *line)
{
	char	**cmd;
	char	*start;
	char	*end;
	int		i;

	cmd = NULL;
	start = line;
	end = line;
	i = 0;
	while (*end)
	{
		while (*start && *start == ' ')
			start++;
		end = find_end(start);
		cmd = resize_cmd(cmd, i);
		cmd[i] = ft_strncpy(malloc(end - start + 1), start, end - start);
		cmd[i][end - start] = '\0';
		cmd[i] = assign_variable(cmd[i]);
		strip_quotes(cmd[i]);
		i++;
		start = end;
	}
	cmd = resize_cmd(cmd, i);
	cmd[i] = NULL;
	return (cmd);
}

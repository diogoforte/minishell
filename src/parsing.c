/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 19:07:51 by dinunes-         ###   ########.fr       */
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
		cmd = NULL;
	}
	return (new_cmd);
}


void	strip_quotes(char *arg)
{
	int	arg_len;
	int	quote_count1;
	int	quote_count2;
	int	i;

	arg_len = ft_strlen(arg);
	quote_count1 = 0;
	quote_count2 = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			quote_count1++;
		if (arg[i] == '"')
			quote_count2++;
		i++;
	}
	if ((quote_count1 == 2 || quote_count2 == 2) && (arg[0] == '"'
			|| arg[0] == '\''))
	{
		ft_memmove(arg, arg + 1, arg_len - 1);
		arg[arg_len - 2] = '\0';
	}
}

char	**parse_cmd(char *line, char ***envp)
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
		start = skip_spaces(start);
		end = find_end(start);
		start = process_cmd(start, &end, &cmd, &i, envp);
		start = end + 1;
	}
	cmd = resize_cmd(cmd, i);
	cmd[i] = NULL;
	return (cmd);
}

char	*skip_spaces(char *start)
{
	while (*start && *start == ' ')
		start++;
	return (start);
}

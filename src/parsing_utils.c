/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/07/31 12:05:45 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*find_end_of_arg(char *start)
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

char	**resize_args(char **args, int count)
{
	char	**new_args;

	new_args = malloc((count + 2) * sizeof(char *));
	if (args != NULL)
	{
		ft_memcpy(new_args, args, count * sizeof(char *));
		free(args);
	}
	return (new_args);
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

char	**parse_args(char *line)
{
	char	**args;
	char	*start;
	char	*end;
	int		count;

	args = NULL;
	start = line;
	end = line;
	count = 0;
	while (*end)
	{
		while (*start && *start == ' ')
			start++;
		end = find_end_of_arg(start);
		args = resize_args(args, count);
		args[count] = ft_strncpy(malloc(end - start + 1), start, end - start);
		args[count][end - start] = '\0';
		strip_quotes(args[count]);
		count++;
		start = end;
	}
	args = resize_args(args, count);
	args[count] = NULL;
	return (args);
}

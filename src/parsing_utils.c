/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 12:00:56 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 01:59:21 by dinunes-         ###   ########.fr       */
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
		while (*start && *start == ' ')
			start++;
		end = find_end(start);
		if (!ft_strncmp(start, ">", 1) || !ft_strncmp(start, ">>", 2))
		{
			if (*start == '>' && *(start + 1) != '>')
			{
				get_redirections()->out_redir = 1;
				start++;
			}
			else
			{
				get_redirections()->out_redir = 2;
				start += 2;
			}
			while (*start && *start == ' ')
				start++;
			end = find_end(start);
			get_redirections()->out_file = ft_strncpy(malloc(end - start + 1),
				start, end - start);
			get_redirections()->out_file[end - start] = '\0';
		}
		else if (ft_strncmp(start, "<<", 2) == 0)
		{
			get_redirections()->in_redir = 2;
			start = start + 2;
			end = find_end(start);
			get_redirections()->heredoc = create_heredoc_file(start, envp);
		}
		else if (ft_strncmp(start, "<", 1) == 0)
		{
			get_redirections()->in_redir = 1;
			start++;
			while (*start && *start == ' ')
				start++;
			end = find_end(start);
			get_redirections()->in_file = ft_strncpy(malloc(end - start + 1),
				start, end - start);
			get_redirections()->in_file[end - start] = '\0';
		}
		else
		{
			cmd = resize_cmd(cmd, i);
			cmd[i] = ft_strncpy(malloc(end - start + 1), start, end - start);
			cmd[i][end - start] = '\0';
			cmd[i] = assign_variable(cmd[i], envp);
			strip_quotes(cmd[i]);
			i++;
		}
		start = end;
	}
	cmd = resize_cmd(cmd, i);
	cmd[i] = NULL;
	return (cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:19:33 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/04 09:04:59 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*assign_variable(char *cmd, char ***envp)
{
	t_cmd_parser	parser;
	int				status;

	parser.cmd = &cmd;
	parser.envp = envp;
	if (check_quotes(cmd) || check_apostrophe(cmd))
		return (cmd);
	parser.start = ft_strchr(cmd, '$');
	if (!parser.start)
		return (cmd);
	if (parser.start[0] == '$' && parser.start[1] == '?')
	{
		status = *exit_status(NULL);
		return (ft_itoa(status));
	}
	parser.end = find_var_end(parser.start);
	parser.i = parser.end - parser.start - 1;
	parser.cmd[0] = ft_strncpy(malloc(parser.i), parser.start + 1, parser.i);
	parser.cmd[0][parser.i] = '\0';
	parser.cmd[1] = get_env(envp, parser.cmd[0]);
	if (!parser.cmd[1])
		parser.cmd[1] = "";
	return (assign_variable(create_new_cmd(&parser), envp));
}

int	check_quotes(char *cmd)
{
	int		open_quotes;
	char	*tmp;

	open_quotes = 0;
	tmp = cmd;
	while (*tmp)
	{
		if (*tmp == '\'')
			open_quotes = !open_quotes;
		tmp++;
	}
	return (open_quotes);
}

int	check_apostrophe(char *cmd)
{
	int		apostrophe;
	char	*tmp;

	apostrophe = 0;
	tmp = cmd;
	while (*tmp)
	{
		if (*tmp == '\'')
		{
			apostrophe = 1;
			break ;
		}
		tmp++;
	}
	return (apostrophe);
}

char	*find_var_end(char *var_start)
{
	char	*var_end;

	var_end = var_start + 1;
	while (*var_end && (ft_isalnum(*var_end) || *var_end == '_'))
		var_end++;
	return (var_end);
}

char	*create_new_cmd(t_cmd_parser *parser)
{
	char	*new_cmd;

	new_cmd = malloc(strlen(*parser->cmd) - strlen(parser->cmd[0])
			+ strlen(parser->cmd[1]));
	ft_strncpy(new_cmd, *parser->cmd, parser->start - *parser->cmd);
	new_cmd[parser->start - *parser->cmd] = '\0';
	ft_strcat(new_cmd, parser->cmd[1]);
	ft_strcat(new_cmd, parser->end);
	free(parser->cmd[0]);
	free(*parser->cmd);
	return (new_cmd);
}

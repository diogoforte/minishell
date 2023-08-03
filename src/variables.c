/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_variable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:19:33 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/03 09:18:57 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*assign_variable(char *cmd, char ***envp)
{
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
	int		status;

	if (check_quotes(cmd) || check_apostrophe(cmd))
		return (cmd);
	var_start = ft_strchr(cmd, '$');
	if (!var_start)
		return (cmd);
	if (var_start[0] == '$' && var_start[1] == '?')
	{
		status = *exit_status(NULL);
		return (ft_itoa(status));
	}
	var_end = find_var_end(var_start);
	var_name = ft_strncpy(malloc(var_end - var_start), var_start + 1, var_end
			- var_start - 1);
	var_name[var_end - var_start - 1] = '\0';
	var_value = get_env(envp, var_name);
	if (!var_value)
		var_value = "";
	return (assign_variable(create_new_cmd(cmd, var_start, var_end, var_name,
				var_value), envp));
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

char	*create_new_cmd(char *cmd, char *var_start, char *var_end,
		char *var_name, char *var_value)
{
	char	*new_cmd;

	new_cmd = malloc(strlen(cmd) - strlen(var_name) - 1 + strlen(var_value)
			+ 1);
	ft_strncpy(new_cmd, cmd, var_start - cmd);
	new_cmd[var_start - cmd] = '\0';
	ft_strcat(new_cmd, var_value);
	ft_strcat(new_cmd, var_end);
	free(var_name);
	free(cmd);
	return (new_cmd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:19:33 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/18 17:16:19 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*assign_variable(char *cmd, char ***envp, int flag)
{
	t_variables	var;
	char		*new_cmd;

	if (check_quotes(cmd) || check_apostrophe(cmd))
		return (cmd);
	var.start = ft_strchr(cmd, '$');
	if (!var.start || (!ft_isalnum(*(var.start + 1)) && *(var.start
				+ 1) != '?'))
		return (cmd);
	if (var.start[0] == '$' && var.start[1] == '?')
	{
		free(cmd);
		return (ft_itoa(*exit_status(NULL)));
	}
	var.end = find_var_end(var.start);
	var.name = ft_strncpy(ft_calloc(var.end - var.start, sizeof(char)),
			var.start + 1, var.end - var.start - 1);
	var.value = search_env(envp, var.name);
	if (!var.value)
		var.value = "";
	new_cmd = create_new_cmd(&var, cmd);
	if (flag)
		free(cmd);
	return (new_cmd);
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

char	*create_new_cmd(t_variables *var, char *cmd)
{
	char	*new_cmd;

	new_cmd = malloc(ft_strlen(cmd) - ft_strlen(var->name) - 1
			+ ft_strlen(var->value) + 1);
	ft_strncpy(new_cmd, cmd, var->start - cmd);
	new_cmd[var->start - cmd] = '\0';
	ft_strcat(new_cmd, var->value);
	ft_strcat(new_cmd, var->end);
	free(var->name);
	return (new_cmd);
}

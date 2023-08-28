/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 06:19:33 by dinunes-          #+#    #+#             */
/*   Updated: 2023/08/28 22:28:29 by bcastelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*assign_variable(char *cmd, char ***envp, int flag)
{
	t_variables	var;
	char		*new_cmd;

	if (!check_var_assign(cmd))
		return (cmd);
	var.start = ft_strchr(cmd, '$');
	if (!var.start || (!ft_isalnum(*(var.start + 1)) && *(var.start
				+ 1) != '?'))
		return (cmd);
	var.end = find_var_end(var.start);
	var.name = ft_strncpy(ft_calloc(var.end - var.start, sizeof(char)),
			var.start + 1,
			var.end - var.start - 1);
	var.value = search_env(envp, var.name);
	if (!var.value)
		var.value = "";
	new_cmd = create_new_cmd(&var, cmd);
	if (*(var.start + 1) == '?')
		free(var.value);
	if (flag)
		free(cmd);
	new_cmd = assign_variable(new_cmd, envp, 1);
	return (new_cmd);
}

void	swap_single_quote_state(t_in_quote *state, char q)
{
	if (q == '"' && !state->sing)
		state->doub = !state->doub;
	if (q == '\'' && !state->doub)
		state->sing = !state->sing;
	state->inside = state->sing;
}

int	check_var_assign(char *cmd)
{
	t_in_quote	state;

	init_quote_state(&state);
	while (*cmd)
	{
		swap_single_quote_state(&state, *cmd);
		if (*cmd == '$' && !state.inside)
			return (1);
		cmd++;
	}
	return (0);
}

char	*find_var_end(char *var_start)
{
	char	*var_end;

	var_end = var_start + 1;
	if (*var_end == '?')
		return (var_end + 1);
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

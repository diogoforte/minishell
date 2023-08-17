/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:18:07 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/17 18:24:43 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	init_quote_state(t_in_quote *state)
{
	state->doub = 0;
	state->sing = 0;
	state->inside = 0;
}

void	swap_quote_state(t_in_quote *state, char q)
{
	if (q == '"' && !state->sing)
		state->doub = !state->doub;
	if (q == '\'' && !state->doub)
		state->sing = !state->sing;
	state->inside = state->doub + state->sing;
}

static int	pipec(char const *s, char c)
{
	int			i;
	t_in_quote	state;

	init_quote_state(&state);
	i = 0;
	while (*s)
	{
		swap_quote_state(&state, *s);
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && (*s != c || state.inside))
			{
				swap_quote_state(&state, *s);
				s++;
			}
		}
	}
	return (i);
}

static size_t	cmd_size(const char *str, int n, char c)
{
	size_t		i;
	t_in_quote	state;

	init_quote_state(&state);
	i = 0;
	while (str[++n] && (str[n] != c || state.inside))
	{
		swap_quote_state(&state, str[n]);
		i++;
	}
	return (i);
}

char	**split_pipes(const char *str, char c)
{
	char		**ret;
	int			size;
	int			j;
	int			i;
	t_in_quote	state;

	init_quote_state(&state);
	i = 0;
	j = -1;
	size = pipec(str, c);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = NULL;
	while (++j < size)
	{
		while (str[i] && (str[i] == c || state.inside))
			swap_quote_state(&state, str[i++]);
		if (str[i] && str[i] != c && !state.inside)
			ret[j] = ft_substr(str, i, cmd_size(str, i - 1, c));
		while (str[i] && (str[i] != c || state.inside))
			swap_quote_state(&state, str[i++]);
	}
	return (ret);
}

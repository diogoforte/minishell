/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/15 17:18:07 by bcastelo          #+#    #+#             */
/*   Updated: 2023/08/16 02:19:07 by dinunes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

typedef struct s_in_quote
{
	int			doub;
	int			sing;
	int			inside;
}				t_in_quote;

void	swap_quote_state(t_in_quote *state, char q)
{
	if (q == '"' && !state->sing)
		state->doub = !state->doub;
	if (q == '\'' && !state->doub)
		state->sing = !state->sing;
	state->inside = state->doub + state->sing;
	printf("%c - %d %d %d\n", q, state->doub, state->sing, state->inside);
}

static int	pipec(char const *s, char c)
{
	int			i;
	t_in_quote	state;

	i = 0;
	state.doub = 0;
	state.sing = 0;
	state.inside = 0;
	while (*s)
	{
		if (*s == '"' || *s == '\'')
			swap_quote_state(&state, *s);
		if (*s == c)
			s++;
		else
		{
			i++;
			while (*s && (*s != c || !state.inside))
			{
				if (*s == '"' || *s == '\'')
					swap_quote_state(&state, *s);
				s++;
			}
		}
	}
	return (i);
}

static size_t	cmd_size(const char *str, int n, char c)
{
	size_t	i;

	i = 0;
	while (str[++n] && str[n] != c)
		i++;
	return (i);
}

char	**split_pipes(const char *str, char c)
{
	char	**ret;
	int		size;
	int		j;
	int		i;

	i = 0;
	j = -1;
	size = pipec(str, c);
	ret = (char **)malloc(sizeof(char *) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = NULL;
	while (++j < size)
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			ret[j] = ft_substr(str, i, cmd_size(str, i - 1, c));
		while (str[i] && str[i] != c)
			i++;
	}
	return (ret);
}

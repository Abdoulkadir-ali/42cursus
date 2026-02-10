/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 23:40:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*generate_tmp_filename(int *fd_out)
{
	char	tmpl[32];

	ft_strcpy(tmpl, "/tmp/.minishell_heredoc_XXXXXX");
	*fd_out = mkstemp(tmpl);
	if (*fd_out == -1)
		return (NULL);
	fchmod(*fd_out, 0644);
	return (ft_strdup(tmpl));
}

int	is_quoted_delim(const char *delim)
{
	int	i;

	if (!delim)
		return (0);
	i = 0;
	while (delim[i])
	{
		if (delim[i] == '\'' || delim[i] == '"' || delim[i] == '\\')
			return (1);
		i++;
	}
	return (0);
}

static void	handle_inside_quote(const char *str, char *res,
		t_quotes_state *state)
{
	if (str[state->i] == state->quote)
	{
		state->quote = 0;
		state->i++;
	}
	else
	{
		res[state->j++] = str[state->i++];
	}
}

static void	handle_outside_quote(const char *str, char *res,
		t_quotes_state *state)
{
	if (str[state->i] == '\\')
	{
		state->i++;
		if (str[state->i])
			res[state->j++] = str[state->i++];
	}
	else if (str[state->i] == '\'' || str[state->i] == '"')
		state->quote = str[state->i++];
	else
		res[state->j++] = str[state->i++];
}

char	*remove_quotes_heredoc(char *str)
{
	char			*res;
	t_quotes_state	state;

	if (!str)
		return (NULL);
	state.i = 0;
	state.j = 0;
	state.quote = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[state.i])
	{
		if (state.quote)
			handle_inside_quote(str, res, &state);
		else
			handle_outside_quote(str, res, &state);
	}
	res[state.j] = '\0';
	return (res);
}

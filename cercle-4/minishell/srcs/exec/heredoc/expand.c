/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:57:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	process_expand_char(t_expansion *exp)
{
	if (handle_backslash_split(&exp->input, &exp->state, &exp->output))
		return (1);
	if (handle_quote_split(&exp->input, &exp->state, &exp->output))
		return (1);
	if (handle_dollar_split(&exp->input, &exp->state, &exp->output))
		return (1);
	return (0);
}

char	*expand_string(char *str, char **env, int status)
{
	t_expansion	exp;

	if (!str)
		return (NULL);
	ft_bzero(&exp, sizeof(t_expansion));
	exp.input.str = str;
	exp.input.env = env;
	exp.input.status = status;
	exp.output.str = ft_strdup("");
	if (!exp.output.str)
		return (NULL);
	while (exp.input.str[exp.input.pos])
	{
		if (process_expand_char(&exp))
			continue ;
		exp_push_char(&exp.output, exp.input.str[exp.input.pos]);
		exp.input.pos++;
	}
	return (exp.output.str);
}

char	*expand_heredoc(char *str, char **env, int status)
{
	char	*expanded;
	char	*tmp;
	int		pos;

	pos = 0;
	expanded = ft_strdup("");
	while (str[pos])
	{
		if (str[pos] == '$')
		{
			if (str[pos + 1] == '?' || is_var_char(str[pos + 1]))
			{
				tmp = handle_dollar(str, &pos, env, status);
				append_chunk(&expanded, tmp);
				continue ;
			}
		}
		tmp = ft_substr(str, pos, 1);
		append_chunk(&expanded, tmp);
		pos++;
	}
	return (expanded);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:15:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_expand_char(t_expansion *exp)
{
	if (handle_backslash_split(&exp->params, &exp->quotes, &exp->buffers))
		return (1);
	if (handle_quote_split(&exp->params, &exp->quotes, &exp->buffers))
		return (1);
	if (handle_dollar_split(&exp->params, &exp->quotes, &exp->buffers))
		return (1);
	return (0);
}

char	*expand_string(char *str, char **env, int status)
{
	t_expansion	exp;

	if (!str)
		return (NULL);
	ft_bzero(&exp, sizeof(t_expansion));
	exp.params.str = str;
	exp.params.env = env;
	exp.params.status = status;
	exp.buffers.expanded = ft_strdup("");
	if (!exp.buffers.expanded)
		return (NULL);
	while (exp.params.str[exp.params.pos])
	{
		if (process_expand_char(&exp))
			continue ;
		append_chunk(&exp.buffers.expanded,
			ft_substr(exp.params.str, exp.params.pos, 1));
		exp.params.pos++;
	}
	return (exp.buffers.expanded);
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

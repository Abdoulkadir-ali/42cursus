/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:26:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether a character is valid inside a variable name.
 * @param c Character being inspected after a dollar sign.
 * @return 1 for alphanumeric or underscore, otherwise 0.
 */
static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * @brief Run one expansion step while scanning a generic string.
 * @param exp Expansion state holding input and output buffers.
 * @return 1 when a handler consumed the current input, otherwise 0.
 */
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

/**
 * @brief Expand shell syntax in a generic string.
 * @param str Source string to expand.
 * @param env Environment array used for variable lookup.
 * @param status Last shell exit status used for `$?`.
 * @return Newly allocated expanded string, or NULL on failure.
 */
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

/**
 * @brief Expand only heredoc-supported variables inside one line.
 * @param str Source heredoc line.
 * @param env Environment array used for variable lookup.
 * @param status Last shell exit status used for `$?`.
 * @return Newly allocated expanded line.
 */
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

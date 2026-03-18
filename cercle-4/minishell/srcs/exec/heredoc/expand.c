/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:36 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:16:37 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Check whether a character is valid inside a variable name.
 * @param c Character being inspected after a dollar sign.
 * @return True for alphanumeric or underscore, otherwise false.
 */
static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * @brief Run one expansion step while scanning a generic string.
 * @param exp Expansion context holding state and buffers.
 * @return 1 when a handler consumed the current input, otherwise 0.
 */
static int	process_expand_char(t_expansion *exp)
{
	if (handle_backslash_split(exp))
		return (1);
	if (handle_quote_split(exp))
		return (1);
	if (handle_dollar_split(exp))
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
	exp.str = str;
	exp.env = env;
	exp.status = status;
	exp.res_str = ft_strdup("");
	if (!exp.res_str)
		return (NULL);
	while (exp.str[exp.pos])
	{
		if (process_expand_char(&exp))
			continue ;
		exp_push_char(&exp, exp.str[exp.pos]);
		exp.pos++;
	}
	return (exp.res_str);
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
	size_t	pos;

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

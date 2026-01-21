/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extender.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 05:35:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 05:57:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"


typedef struct s_opmap
{
	char				code;
	const char			*symbol;
	const char			*label;
}						t_opmap;

static const t_opmap	g_opmap[] = {{'|', "|", "pipe"}, {'o', "||", "or"},
		{'a', "&&", "and"}, {'>', ">", "redir_out"}, {'R', ">>", "append"},
		{'<', "<", "redir_in"}, {'h', "<<", "heredoc"}, {'t', "<<<",
		"herestring"}, {'\'', "'", "quote"}, {'"', "\"", "dquote"}, {'p', "(",
		"paren"}, {0, NULL, NULL}};

typedef struct s_cont
{
	const char			*sym;
	char				code;
	const char			*label;
}						t_cont;

static const t_cont		g_cont_map[] = {{"<<<", 't', "herestring"}, {"<<", 'h',
			"heredoc"}, {">>", 'R', "append"}, {"||", 'o', "or"}, {"&&", 'a',
			"and"}, {"|", '|', "pipe"}, {"&", '&', "amp"}, {">", '>',
			"redir_out"}, {"<", '<', "redir_in"}, {NULL, 0, NULL}};

/* Return label associated with continuation code */
const char	*ext_continuation_label(char kind)
{
	const t_opmap	*m = g_opmap;

	while (m->code)
	{
		if (m->code == kind)
			return (m->label);
		m++;
	}
	return (NULL);
}

/* helper: last non-space character pointer */
static char	*last_non_space_local(char *s)
{
	char	*p;

	if (!s || !*s)
		return (NULL);
	p = s + ft_strlen(s) - 1;
	while (p >= s && ft_isspace(*p))
		p--;
	if (p < s)
		return (NULL);
	return (p);
}

/* Detect trailing operator; returns code from g_cont_map or 0 */
char	ext_detect_trailing_op(char *line)
{
	char	*p;
	int		i;
	int		len;
	char	*start;
			int k;

	p = last_non_space_local(line);
	if (!p)
		return (0);
	i = 0;
	while (g_cont_map[i].sym)
	{
		len = ft_strlen(g_cont_map[i].sym);
		start = p - (len - 1);
		if (start >= line)
		{
			k = 0;
			while (k < len)
			{
				if (start[k] != g_cont_map[i].sym[k])
					break ;
				k++;
			}
			if (k == len)
				return (g_cont_map[i].code);
		}
		i++;
	}
	return (0);
}

/* Return number of unmatched '(' minus ')' ignoring quoted sections */
int	ext_check_paren_depth(char *s)
{
	int		depth;
	char	quote;

	depth = 0;
	quote = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (quote == 0)
		{
			if (*s == '\'' || *s == '"')
				quote = *s;
			else if (*s == '(')
				depth++;
			else if (*s == ')')
				depth--;
		}
		else
		{
			if (*s == quote)
				quote = 0;
		}
		s++;
	}
	return (depth);
}

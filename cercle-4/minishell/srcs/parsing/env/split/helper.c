/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 03:58:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:22:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	process_val_split(char *val, t_exp_ctx *ctx)
{
	int		k;
	char	buf[2];

	if (!val || !*val)
		return ;
	k = 0;
	while (val[k])
	{
		if (ft_isspace(val[k]))
		{
			if (ctx->state.curr && *ctx->state.curr)
			{
				add_token_node(ctx->lists.head, ctx->lists.tail,
					*ctx->state.curr, *ctx->state.wd_quoted);
				*ctx->state.curr = NULL;
				*ctx->state.wd_quoted = 0;
			}
		}
		else
		{
			buf[0] = val[k];
			buf[1] = '\0';
			if (ctx->state.res)
				append_chunk(ctx->state.res, ft_strdup(buf));
			else
				append_chunk(ctx->state.curr, ft_strdup(buf));
			if (ctx->state.wd_quoted)
				*ctx->state.wd_quoted = 0;
		}
		k++;
	}
}

int	handle_quote_split(t_exp_ctx *ctx)
{
	if (ctx->input.str[*ctx->state.i] == '\'' && !ctx->state.qt[1])
	{
		ctx->state.qt[0] = !ctx->state.qt[0];
		if (ctx->state.res == NULL)
		{
			*ctx->state.wd_quoted = 1;
			if (!*ctx->state.curr)
				*ctx->state.curr = ft_strdup("");
		}
		(*ctx->state.i)++;
		return (1);
	}
	if (ctx->input.str[*ctx->state.i] == '"' && !ctx->state.qt[0])
	{
		ctx->state.qt[1] = !ctx->state.qt[1];
		if (ctx->state.res == NULL)
		{
			*ctx->state.wd_quoted = 1;
			if (!*ctx->state.curr)
				*ctx->state.curr = ft_strdup("");
		}
		(*ctx->state.i)++;
		return (1);
	}
	return (0);
}

int	handle_backslash_split(t_exp_ctx *ctx)
{
	char	*tmp;

	if (ctx->input.str[*ctx->state.i] != '\\' || ctx->state.qt[0])
		return (0);
	if (ctx->state.qt[1] && ctx->input.str[*ctx->state.i + 1] != '$'
		&& ctx->input.str[*ctx->state.i + 1] != '"'
		&& ctx->input.str[*ctx->state.i + 1] != '\\'
		&& ctx->input.str[*ctx->state.i + 1] != '\n')
	{
		tmp = ft_substr(ctx->input.str, *ctx->state.i, 1);
		if (ctx->state.res)
			append_chunk(ctx->state.res, tmp);
		else
			append_chunk(ctx->state.curr, tmp);
		(*ctx->state.i)++;
		return (1);
	}
	(*ctx->state.i)++;
	if (ctx->input.str[*ctx->state.i])
	{
		tmp = ft_substr(ctx->input.str, *ctx->state.i, 1);
		if (ctx->state.res)
			append_chunk(ctx->state.res, tmp);
		else
		{
			append_chunk(ctx->state.curr, tmp);
			if (ctx->state.wd_quoted)
				*ctx->state.wd_quoted = 1;
		}
		(*ctx->state.i)++;
	}
	return (1);
}

int	handle_dollar_split(t_exp_ctx *ctx)
{
	char	*val;
	char	*tmp;

	if (ctx->input.str[*ctx->state.i] != '$')
		return (0);
	if (ctx->state.res)
	{
		if (ctx->input.str[*ctx->state.i + 1] == '\''
			|| ctx->input.str[*ctx->state.i + 1] == '$'
			|| (!is_var_char(ctx->input.str[*ctx->state.i + 1])
			&& ctx->input.str[*ctx->state.i + 1] != '"'
			&& ctx->input.str[*ctx->state.i + 1] != '?'))
		{
			tmp = ft_substr(ctx->input.str, *ctx->state.i, 1);
			append_chunk(ctx->state.res, tmp);
			(*ctx->state.i)++;
			return (1);
		}
		if (!ctx->state.qt[0]
			&& (ft_isalnum((unsigned char)ctx->input.str[*ctx->state.i + 1])
				|| ctx->input.str[*ctx->state.i + 1] == '_'
				|| ctx->input.str[*ctx->state.i + 1] == '?'))
		{
			tmp = handle_dollar((char *)ctx->input.str, ctx->state.i,
					ctx->input.envp, ctx->input.exit_code);
			append_chunk(ctx->state.res, tmp);
			return (1);
		}
	}
	else
	{
		if ((ctx->input.str[*ctx->state.i + 1] == '\''
				|| ctx->input.str[*ctx->state.i + 1] == '"')
				&& !ctx->state.qt[0] && !ctx->state.qt[1])
		{
			(*ctx->state.i)++;
			return (1);
		}
		if ((!is_var_char(ctx->input.str[*ctx->state.i + 1])
				&& ctx->input.str[*ctx->state.i + 1] != '?') || ctx->state.qt[0]
			|| (ctx->input.str[*ctx->state.i + 1] == '"' && ctx->state.qt[1]))
		{
			append_chunk(ctx->state.curr, ft_substr(ctx->input.str,
					*ctx->state.i, 1));
			(*ctx->state.i)++;
			return (1);
		}
		val = handle_dollar((char *)ctx->input.str, ctx->state.i,
				ctx->input.envp, ctx->input.exit_code);
		if (ctx->state.qt[1])
		{
			append_chunk(ctx->state.curr, val);
			*ctx->state.wd_quoted = 1;
		}
		else
		{
			process_val_split(val, ctx);
			free(val);
		}
		return (1);
	}
	return (0);
}

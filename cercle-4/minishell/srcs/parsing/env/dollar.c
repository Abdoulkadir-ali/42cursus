/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:01:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:57:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	handle_quote_split(t_exp_ctx *ctx)
{
	if (ctx->str[*ctx->i] == '\'' && !ctx->qt[1])
	{
		ctx->qt[0] = !ctx->qt[0];
		*ctx->wd_quoted = 1;
		if (!*ctx->curr)
			*ctx->curr = ft_strdup("");
		(*ctx->i)++;
		return (1);
	}
	if (ctx->str[*ctx->i] == '"' && !ctx->qt[0])
	{
		ctx->qt[1] = !ctx->qt[1];
		*ctx->wd_quoted = 1;
		if (!*ctx->curr)
			*ctx->curr = ft_strdup("");
		(*ctx->i)++;
		return (1);
	}
	return (0);
}

int	handle_backslash_split(t_exp_ctx *ctx)
{
	char	*tmp;

	if (ctx->str[*ctx->i] != '\\' || ctx->qt[0])
		return (0);
	if (ctx->qt[1] && ctx->str[*ctx->i + 1] != '$' && ctx->str[*ctx->i
		+ 1] != '"' && ctx->str[*ctx->i + 1] != '\\' && ctx->str[*ctx->i
		+ 1] != '\n')
	{
		tmp = ft_substr(ctx->str, *ctx->i, 1);
		append_chunk(ctx->curr, tmp);
		(*ctx->i)++;
		return (1);
	}
	(*ctx->i)++;
	if (ctx->str[*ctx->i])
	{
		tmp = ft_substr(ctx->str, *ctx->i, 1);
		append_chunk(ctx->curr, tmp);
		*ctx->wd_quoted = 1;
		(*ctx->i)++;
	}
	return (1);
}

static void	process_val_split(char *val, t_exp_ctx *ctx)
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
			if (*ctx->curr)
			{
				add_token_node(ctx->head, ctx->tail, *ctx->curr,
					*ctx->wd_quoted);
				*ctx->curr = NULL;
				*ctx->wd_quoted = 0;
			}
		}
		else
		{
			buf[0] = val[k];
			buf[1] = '\0';
			append_chunk(ctx->curr, ft_strdup(buf));
			*ctx->wd_quoted = 0;
		}
		k++;
	}
}

int	handle_dollar_split(t_exp_ctx *ctx)
{
	char	*val;

	if (ctx->str[*ctx->i] != '$')
		return (0);
	if ((ctx->str[*ctx->i + 1] == '\'' || ctx->str[*ctx->i + 1] == '"')
			&& !ctx->qt[0] && !ctx->qt[1])
	{
		(*ctx->i)++;
		return (1);
	}
	if ((!is_var_char(ctx->str[*ctx->i + 1]) && ctx->str[*ctx->i + 1] != '?')
		|| ctx->qt[0] || (ctx->str[*ctx->i + 1] == '"' && ctx->qt[1]))
	{
		append_chunk(ctx->curr, ft_substr(ctx->str, *ctx->i, 1));
		(*ctx->i)++;
		return (1);
	}
	val = handle_dollar((char *)ctx->str, ctx->i, ctx->envp, ctx->exit_code);
	if (ctx->qt[1])
	{
		append_chunk(ctx->curr, val);
		*ctx->wd_quoted = 1;
	}
	else
	{
		process_val_split(val, ctx);
		free(val);
	}
	return (1);
}

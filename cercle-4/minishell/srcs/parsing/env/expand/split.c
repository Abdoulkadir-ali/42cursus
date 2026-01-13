/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:19:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	process_val_split(char *val, t_exp_ctx *ctx)
{
	int		k;
	char	buf[2];

	if (!val || !*val)
		return (0);
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
	return (0);
}

static int	handle_quote_split(t_exp_ctx *ctx)
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

static int	handle_backslash_split(t_exp_ctx *ctx)
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

static int	handle_dollar_split(t_exp_ctx *ctx)
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

static void	init_exp_ctx(t_exp_ctx *ctx, char *str, char **envp, int *i,
		int qt[2], int *wd_quoted, char **curr, t_nodes **head, t_nodes **tail,
		int exit_code)
{
	ft_bzero(ctx, sizeof(t_exp_ctx));
	ctx->str = str;
	ctx->i = i;
	ctx->qt = qt;
	ctx->wd_quoted = wd_quoted;
	ctx->curr = curr;
	ctx->head = head;
	ctx->tail = tail;
	ctx->envp = envp;
	ctx->exit_code = exit_code;
}

static void	run_expansion_loop(t_exp_ctx *ctx)
{
	while (ctx->str[*ctx->i])
	{
		if (handle_quote_split(ctx))
			continue ;
		if (handle_backslash_split(ctx))
			continue ;
		if (handle_dollar_split(ctx))
			continue ;
		append_chunk(ctx->curr, ft_substr(ctx->str, *ctx->i, 1));
		if (!ctx->qt[0] && !ctx->qt[1])
			*ctx->wd_quoted = 0;
		(*ctx->i)++;
	}
}

static t_nodes	*finalize_expansion(t_exp_ctx *ctx)
{
	if (*ctx->curr)
		add_token_node(ctx->head, ctx->tail, *ctx->curr, *ctx->wd_quoted);
	else if (*ctx->wd_quoted)
		add_token_node(ctx->head, ctx->tail, ft_strdup(""), 1);
	return (*ctx->head);
}
t_nodes	*expand_and_split(char *str, char **envp, int exit_code)
{
	t_exp_ctx	ctx;
	t_nodes		*head;
	t_nodes		*tail;
	char		*curr;
	int			i;
	int			qt[2];
	int			wd_quoted;

	if (!str)
		return (NULL);
	head = NULL;
	tail = NULL;
	curr = NULL;
	i = 0;
	qt[0] = 0;
	qt[1] = 0;
	wd_quoted = 0;
	init_exp_ctx(&ctx, str, envp, &i, qt, &wd_quoted, &curr, &head, &tail,
		exit_code);
	run_expansion_loop(&ctx);
	return (finalize_expansion(&ctx));
}

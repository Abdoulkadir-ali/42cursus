/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:09:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	handle_backslash_split(t_exp_ctx *ctx)
{
	char	*tmp;

	if (ctx->str[*ctx->i] != '\\' || ctx->qt[0] || !ctx->str[*ctx->i + 1])
		return (0);
	if (ctx->qt[1] && ctx->str[*ctx->i + 1] != '$' && ctx->str[*ctx->i
		+ 1] != '"' && ctx->str[*ctx->i + 1] != '\\' && ctx->str[*ctx->i
		+ 1] != '\n')
	{
		tmp = ft_substr(ctx->str, *ctx->i, 1);
		append_chunk(ctx->res, tmp);
		(*ctx->i)++;
		return (1);
	}
	(*ctx->i)++;
	tmp = ft_substr(ctx->str, *ctx->i, 1);
	append_chunk(ctx->res, tmp);
	(*ctx->i)++;
	return (1);
}

static int	handle_quote_split(t_exp_ctx *ctx)
{
	if (ctx->str[*ctx->i] == '\'' && !ctx->qt[1])
	{
		ctx->qt[0] = !ctx->qt[0];
		(*ctx->i)++;
		return (1);
	}
	if (ctx->str[*ctx->i] == '"' && !ctx->qt[0])
	{
		ctx->qt[1] = !ctx->qt[1];
		(*ctx->i)++;
		return (1);
	}
	if (ctx->str[*ctx->i] == '$' && !ctx->qt[0] && !ctx->qt[1]
		&& (ctx->str[*ctx->i + 1] == '\'' || ctx->str[*ctx->i + 1] == '"'))
	{
		(*ctx->i)++;
		return (1);
	}
	return (0);
}

static int	handle_dollar_split(t_exp_ctx *ctx)
{
	char	*tmp;

	if (ctx->str[*ctx->i] != '$')
		return (0);
	if (ctx->str[*ctx->i + 1] == '\'' || ctx->str[*ctx->i + 1] == '$'
		|| (!is_var_char(ctx->str[*ctx->i + 1]) && ctx->str[*ctx->i + 1] != '"'
		&& ctx->str[*ctx->i + 1] != '?'))
	{
		tmp = ft_substr(ctx->str, *ctx->i, 1);
		append_chunk(ctx->res, tmp);
		(*ctx->i)++;
		return (1);
	}
	if (!ctx->qt[0] && (ft_isalnum((unsigned char)ctx->str[*ctx->i + 1])
			|| ctx->str[*ctx->i + 1] == '_' || ctx->str[*ctx->i + 1] == '?'))
	{
		tmp = handle_dollar((char *)ctx->str, ctx->i, ctx->envp,
				ctx->exit_code);
		append_chunk(ctx->res, tmp);
		return (1);
	}
	return (0);
}

static int	process_expand_char(t_exp_ctx *ctx)
{
	if (handle_backslash_split(ctx))
		return (1);
	if (handle_quote_split(ctx))
		return (1);
	if (handle_dollar_split(ctx))
		return (1);
	return (0);
}

char	*expand_string(char *str, char **envp, int exit_code)
{
	t_exp_ctx	ctx;
	int			i;
	int			qt[2];

	if (!str)
		return (NULL);
	ft_bzero(&ctx, sizeof(t_exp_ctx));
	i = 0;
	qt[0] = 0;
	qt[1] = 0;
	ctx.str = str;
	ctx.i = &i;
	ctx.qt = qt;
	ctx.envp = envp;
	ctx.exit_code = exit_code;
	ctx.res = malloc(sizeof(char *));
	if (ctx.res)
		*(ctx.res) = ft_strdup("");
	else
		return (NULL);
	while (str[i])
	{
		if (process_expand_char(&ctx))
			continue ;
		append_chunk(ctx.res, ft_substr(str, i, 1));
		i++;
	}
	return (*ctx.res);
}

char	*expand_heredoc(char *str, char **envp, int exit_code)
{
	char	*res;
	char	*tmp;
	int		i;

	i = 0;
	res = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] == '?' || is_var_char(str[i + 1]))
			{
				tmp = handle_dollar(str, &i, envp, exit_code);
				append_chunk(&res, tmp);
				continue ;
			}
		}
		tmp = ft_substr(str, i, 1);
		append_chunk(&res, tmp);
		i++;
	}
	return (res);
}
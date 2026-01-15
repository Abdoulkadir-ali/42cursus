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
	if (!str)
		return (NULL);
	ft_bzero(&ctx, sizeof(t_exp_ctx));
	i = 0;
	qt[0] = 0;
	qt[1] = 0;
	ctx.input.str = str;
	ctx.input.envp = envp;
	ctx.input.exit_code = exit_code;
	ctx.state.i = &i;
	ctx.state.qt = qt;
	ctx.state.res = malloc(sizeof(char *));
	if (ctx.state.res)
		*(ctx.state.res) = ft_strdup("");
	else
		return (NULL);
	while (str[i])
	{
		if (process_expand_char(&ctx))
			continue ;
		append_chunk(ctx.state.res, ft_substr(str, i, 1));
		i++;
	}
	return (*ctx.state.res);
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

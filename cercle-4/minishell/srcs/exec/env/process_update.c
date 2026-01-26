/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_update.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:21:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_no_eq(t_export_ctx *ctx)
{
	if (ctx->new_entry)
		free(ctx->new_entry);
}

static void	handle_append(char **envp, t_export_ctx *ctx)
{
	char	*joined;
	char	*tmp;

	if (ft_strchr(envp[ctx->idx], '='))
		joined = ft_strjoin(envp[ctx->idx], ctx->eq + 1);
	else
	{
		tmp = ft_strjoin(ctx->key, "=");
		joined = ft_strjoin(tmp, ctx->eq + 1);
		free(tmp);
	}
	free(envp[ctx->idx]);
	envp[ctx->idx] = joined;
	free(ctx->new_entry);
}

static void	handle_replace(char **envp, t_export_ctx *ctx)
{
	free(envp[ctx->idx]);
	envp[ctx->idx] = ctx->new_entry;
}

void	update_existing_env(char **envp, t_export_ctx *ctx)
{
	if (!ctx->eq)
	{
		handle_no_eq(ctx);
		return ;
	}
	if (ctx->append)
		handle_append(envp, ctx);
	else
		handle_replace(envp, ctx);
}

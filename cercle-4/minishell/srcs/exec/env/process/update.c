/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Append data to an existing environment entry for `export VAR+=...`.
 * @param envp Environment array containing the entry to update.
 * @param ctx Export parsing context with the target index and suffix.
 * @return This function does not return a value.
 */
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

/**
 * @brief Replace an existing environment entry with a new export value.
 * @param envp Environment array containing the entry to replace.
 * @param ctx Export parsing context with the target index and new entry.
 * @return This function does not return a value.
 */
static void	handle_replace(char **envp, t_export_ctx *ctx)
{
	free(envp[ctx->idx]);
	envp[ctx->idx] = ctx->new_entry;
}

/**
 * @brief Apply the export update rules to an existing environment entry.
 * @param envp Environment array containing the matched key.
 * @param ctx Export parsing context with append or replace metadata.
 * @return This function does not return a value.
 */
void	update_existing_env(char **envp, t_export_ctx *ctx)
{
	if (!ctx->eq)
	{
		if (ctx->new_entry)
			free(ctx->new_entry);
		return ;
	}
	if (ctx->append)
		handle_append(envp, ctx);
	else
		handle_replace(envp, ctx);
}

/**
 * @brief Process one export operand against the current shell environment.
 * @param arg Raw export operand.
 * @param state Shell state whose environment must be updated.
 * @return 0 on success, 1 when the identifier is invalid.
 */
int	process_export_arg(char *arg, t_shell_state *state)
{
	t_export_ctx	ctx;

	ft_bzero(&ctx, sizeof(ctx));
	parse_export_arg(arg, &ctx);
	if (!is_valid_ident(ctx.key))
		return (report_invalid_identifier(arg, &ctx));
	ctx.idx = get_env_index(ctx.key, state);
	if (ctx.idx != -1)
		return (process_existing_export(&ctx, &state->envp));
	else
		return (process_new_export(&ctx, &state->envp));
}

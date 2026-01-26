/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:37:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/26 03:24:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	update_existing_env(char **envp, t_export_ctx *ctx)
{
	char	*joined;
	char	*tmp;

	if (!ctx->eq)
	{
		if (ctx->new_entry)
			free(ctx->new_entry);
		return ;
	}
	if (ctx->append)
	{
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
	else
	{
		free(envp[ctx->idx]);
		envp[ctx->idx] = ctx->new_entry;
	}
}

char	*create_appended_entry(t_export_ctx *ctx)
{
	char	*real_entry;
	char	*tmp;

	real_entry = ft_strjoin(ctx->key, "=");
	tmp = real_entry;
	real_entry = ft_strjoin(real_entry, ctx->eq + 1);
	free(tmp);
	return (real_entry);
}

void	push_new_env_entry(char ***envp, char *new_entry)
{
	int		count;
	char	**new_env;
	int		i;

	count = 0;
	while ((*envp)[count])
		count++;
	new_env = ft_calloc(count + 2, sizeof(char *));
	i = -1;
	while (++i < count)
		new_env[i] = (*envp)[i];
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
}

int	process_export_arg(char *arg, char ***envp)
{
	t_export_ctx	ctx;
	char			*real_entry;

	ft_bzero(&ctx, sizeof(ctx));
	parse_export_arg(arg, &ctx);
	if (!is_valid_ident(ctx.key))
		return (report_invalid_identifier(arg, &ctx));
	ctx.idx = get_env_index(ctx.key, *envp);
	if (ctx.idx != -1)
		update_existing_env(*envp, &ctx);
	else
	{
		if (ctx.append && ctx.eq)
		{
			real_entry = create_appended_entry(&ctx);
			free(ctx.new_entry);
			ctx.new_entry = real_entry;
		}
		push_new_env_entry(envp, ctx.new_entry);
	}
	free(ctx.key);
	return (0);
}

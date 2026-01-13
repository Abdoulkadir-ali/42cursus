/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:37:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 03:18:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static void	parse_export_arg(char *arg, t_export_ctx *ctx)
{
	ctx->eq = ft_strchr(arg, '=');
	ctx->append = 0;
	if (ctx->eq)
	{
		if (ctx->eq > arg && *(ctx->eq - 1) == '+')
		{
			ctx->append = 1;
			ctx->key = ft_substr(arg, 0, ctx->eq - arg - 1);
		}
		else
			ctx->key = ft_substr(arg, 0, ctx->eq - arg);
		ctx->new_entry = ft_strdup(arg);
	}
	else
	{
		ctx->key = ft_strdup(arg);
		ctx->new_entry = NULL;
	}
}

static int	report_invalid_identifier(char *arg, t_export_ctx *ctx)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(ctx->key);
	if (ctx->new_entry)
		free(ctx->new_entry);
	return (1);
}

void	update_existing_env(char **envp, t_export_ctx *ctx)
{
	char	*joined;

	if (!ctx->eq)
	{
		if (ctx->new_entry)
			free(ctx->new_entry);
		return ;
	}
	if (ctx->append)
	{
		joined = ft_strjoin(envp[ctx->idx], ctx->eq + 1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:57:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

	count = count_env(*envp);
	new_env = ft_calloc(count + 2, sizeof(char *));
	i = -1;
	while (++i < count)
		new_env[i] = (*envp)[i];
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
}

int	process_existing_export(t_export_ctx *ctx, char ***envp)
{
	update_existing_env(*envp, ctx);
	free(ctx->key);
	return (0);
}

int	process_new_export(t_export_ctx *ctx, char ***envp)
{
	char	*real_entry;

	if (ctx->append && ctx->eq)
	{
		real_entry = create_appended_entry(ctx);
		free(ctx->new_entry);
		ctx->new_entry = real_entry;
	}
	push_new_env_entry(envp, ctx->new_entry);
	free(ctx->key);
	return (0);
}

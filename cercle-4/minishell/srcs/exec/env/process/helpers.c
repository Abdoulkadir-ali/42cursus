/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Build the final KEY=VALUE entry used by export append mode.
 * @param ctx Export parsing context containing the parsed key and suffix.
 * @return Newly allocated environment entry.
 */
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

/**
 * @brief Append a new entry to an environment array without shell-state sync.
 * @param envp Address of the environment array being extended.
 * @param new_entry Newly allocated environment entry.
 * @return This function does not return a value.
 */
void	push_new_env_entry(char ***envp, char *new_entry)
{
	int		count;
	char	**new_env;

	count = count_env(*envp);
	new_env = ft_calloc(count + 2, sizeof(char *));
	if (!new_env)
		return ;
	ft_memcpy(new_env, *envp, count * sizeof(char *));
	new_env[count] = new_entry;
	free(*envp);
	*envp = new_env;
}

/**
 * @brief Update an already existing environment variable during export.
 * @param ctx Export parsing context with the resolved index.
 * @param envp Address of the environment array being updated.
 * @return Always returns 0.
 */
int	process_existing_export(t_export_ctx *ctx, char ***envp)
{
	update_existing_env(*envp, ctx);
	free(ctx->key);
	return (0);
}

/**
 * @brief Add a new variable to the environment during export.
 * @param ctx Export parsing context describing the new variable.
 * @param envp Address of the environment array being extended.
 * @return Always returns 0.
 */
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

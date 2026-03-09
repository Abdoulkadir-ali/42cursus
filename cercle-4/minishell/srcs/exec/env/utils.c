/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:46:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:22:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Count the number of entries stored in an environment array.
 * @param envp NULL-terminated environment array.
 * @return Number of non-NULL entries.
 */
int	count_env(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

/**
 * @brief Validate a shell identifier used by export or unset.
 * @param str Candidate identifier string.
 * @return 1 when the identifier is valid, else 0.
 */
int	is_valid_ident(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (!ft_isalpha((unsigned char)str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum((unsigned char)str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Split one export operand into the key and provisional entry fields.
 * @param arg Raw export operand.
 * @param ctx Export parsing context updated in place.
 * @return This function does not return a value.
 */
static void	set_key_and_entry(char *arg, t_export_ctx *ctx)
{
	if (ctx->append)
		ctx->key = ft_substr(arg, 0, ctx->eq - arg - 1);
	else
		ctx->key = ft_substr(arg, 0, ctx->eq - arg);
	ctx->new_entry = ft_strdup(arg);
}

/**
 * @brief Parse one export operand into the reusable export context.
 * @param arg Raw export operand.
 * @param ctx Export parsing context updated in place.
 * @return This function does not return a value.
 */
void	parse_export_arg(char *arg, t_export_ctx *ctx)
{
	ctx->eq = ft_strchr(arg, '=');
	ctx->append = 0;
	if (ctx->eq)
	{
		if (ctx->eq > arg && *(ctx->eq - 1) == '+')
			ctx->append = 1;
		set_key_and_entry(arg, ctx);
	}
	else
	{
		ctx->key = ft_strdup(arg);
		ctx->new_entry = ft_strjoin(ctx->key, "=");
	}
}

/**
 * @brief Report an invalid export identifier and release parsed resources.
 * @param arg Raw operand that failed validation.
 * @param ctx Export parsing context holding allocated members.
 * @return Always returns 1.
 */
int	report_invalid_identifier(char *arg, t_export_ctx *ctx)
{
	ft_puterror("export: `%s': not a valid identifier\n", arg);
	free(ctx->key);
	if (ctx->new_entry)
		free(ctx->new_entry);
	return (1);
}

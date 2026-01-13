/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 23:46:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:46:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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

static void	set_key_and_entry(char *arg, t_export_ctx *ctx)
{
	if (ctx->append)
		ctx->key = ft_substr(arg, 0, ctx->eq - arg - 1);
	else
		ctx->key = ft_substr(arg, 0, ctx->eq - arg);
	ctx->new_entry = ft_strdup(arg);
}

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
		ctx->new_entry = ft_strdup(arg);
	}
}

int	report_invalid_identifier(char *arg, t_export_ctx *ctx)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	free(ctx->key);
	if (ctx->new_entry)
		free(ctx->new_entry);
	return (1);
}

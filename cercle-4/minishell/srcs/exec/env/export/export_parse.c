/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_parse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:36:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 02:51:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

void parse_export_arg(char *arg, t_export_ctx *ctx)
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

int report_invalid_identifier(char *arg, t_export_ctx *ctx)
{
    ft_putstr_fd("minishell: export: `", 2);
    ft_putstr_fd(arg, 2);
    ft_putendl_fd("': not a valid identifier", 2);
    free(ctx->key);
    if (ctx->new_entry)
        free(ctx->new_entry);
    return (1);
}

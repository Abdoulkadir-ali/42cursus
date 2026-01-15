/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:22:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_exp_ctx(t_exp_ctx *ctx, char *str, char **envp, int exit_code)
{
	ft_bzero(ctx, sizeof(t_exp_ctx));
	ctx->input.str = str;
	ctx->input.envp = envp;
	ctx->input.exit_code = exit_code;
}

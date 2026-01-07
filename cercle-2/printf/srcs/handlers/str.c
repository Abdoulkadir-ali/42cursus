/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 14:17:40 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 14:17:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_handle_str(t_flags flags, const char *str)
{
	t_str_ctx	ctx;

	ctx.i = 0;
	ctx.tmp = str;
	if (!ctx.tmp)
		ctx.tmp = "(null)";
	ctx.l = ft_strlen(ctx.tmp);
	if (!str && flags.dot && flags.precision < 6)
		ctx.l = 0;
	else if (flags.dot && flags.precision < ctx.l)
		ctx.l = flags.precision;
	ctx.local_flags = flags;
	ctx.local_flags.zero = 0;
	ft_handle_padding(ctx.local_flags, ctx.l, &ctx.i);
	if (ctx.l > 0)
		ctx.i += ft_putnstr(ctx.tmp, ctx.l);
	ft_handle_justify(ctx.local_flags, ctx.l, &ctx.i);
	return (ctx.i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:21:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 16:21:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	get_sign_char(long long nbr, t_flags flags, size_t *nb)
{
	if (nbr < 0)
	{
		*nb = -nbr;
		return ('-');
	}
	else if (flags.plus)
	{
		*nb = nbr;
		return ('+');
	}
	else if (flags.space)
	{
		*nb = nbr;
		return (' ');
	}
	else
	{
		*nb = nbr;
		return (0);
	}
}

static size_t	calculate_num_digits(size_t nb, t_flags flags)
{
	size_t	num_digits;
	size_t	temp;

	temp = nb;
	if (nb == 0)
		num_digits = 1;
	else
	{
		num_digits = 0;
		while (temp > 0)
		{
			temp /= 10;
			num_digits++;
		}
	}
	if (nb == 0 && flags.dot && flags.precision == 0)
		num_digits = 0;
	return (num_digits);
}

static void	init_ctx(t_nbr_ctx *ctx, t_flags flags, va_list args)
{
	long long	nbr;

	if (flags.length == LEN_LL)
		nbr = va_arg(args, long long);
	else if (flags.length == LEN_L)
		nbr = va_arg(args, long);
	else
		nbr = va_arg(args, int);
	ctx->i = 0;
	ctx->sign_c = get_sign_char(nbr, flags, &ctx->nb);
	ctx->sign = (ctx->sign_c != 0);
	ctx->num_digits = calculate_num_digits(ctx->nb, flags);
	ctx->l = ft_apply_precision(ctx->num_digits, flags, ctx->num_digits);
	ctx->total_len = ctx->l + ctx->sign;
	ctx->pad_len = 0;
	if (flags.width > 0 && flags.width > ctx->total_len)
		ctx->pad_len = flags.width - ctx->total_len;
}

static size_t	calculate_zero_pad_len(t_nbr_ctx *ctx, t_flags flags)
{
	size_t	zero_pad_len;

	zero_pad_len = 0;
	if (flags.dot && flags.precision > ctx->num_digits)
		zero_pad_len = flags.precision - ctx->num_digits;
	if (flags.zero && !flags.dot && !flags.minus && ctx->pad_len > 0)
	{
		zero_pad_len = ctx->pad_len;
		ctx->pad_len = 0;
	}
	return (zero_pad_len);
}

size_t	ft_handle_nbr(t_flags flags, va_list args, const char *base)
{
	t_nbr_ctx	ctx;
	size_t		zero_pad_len;

	init_ctx(&ctx, flags, args);
	zero_pad_len = calculate_zero_pad_len(&ctx, flags);
	if (!flags.minus)
		ft_putnchar(' ', ctx.pad_len, &ctx.i);
	ft_handle_sign(ctx.sign_c, &ctx.i);
	ft_putnchar('0', zero_pad_len, &ctx.i);
	if (!(ctx.nb == 0 && flags.dot && flags.precision == 0))
		ft_putnbr_base(ctx.nb, base, &ctx.i);
	if (flags.minus)
		ft_putnchar(' ', ctx.pad_len, &ctx.i);
	return (ctx.i);
}

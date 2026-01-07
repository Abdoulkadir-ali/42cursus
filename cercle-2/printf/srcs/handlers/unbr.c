/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unbr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:21:40 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 16:21:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	get_unsigned_nbr(t_flags flags, va_list args)
{
	if (flags.length == LEN_LL)
		return ((size_t)va_arg(args, unsigned long long));
	else if (flags.length == LEN_L)
		return ((size_t)va_arg(args, unsigned long));
	else
		return ((size_t)va_arg(args, unsigned int));
}

static size_t	ft_get_unbr_size(size_t n, const char *base)
{
	size_t	len;
	size_t	base_len;

	len = 0;
	base_len = ft_strlen(base);
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

static size_t	get_unbr_cl(size_t nb, t_flags flags, const char *base)
{
	size_t	num_digits;
	size_t	l;

	num_digits = ft_get_unbr_size(nb, base);
	if (nb == 0 && flags.dot && flags.precision == 0)
		num_digits = 0;
	l = num_digits;
	l = ft_apply_precision(l, flags, num_digits);
	if (flags.hash && ft_strlen(base) == 16 && nb != 0)
		l += 2;
	return (l);
}

size_t	ft_handle_unbr(t_flags flags, size_t nbr, const char *base)
{
	t_unbr_ctx	ctx;

	ctx.i = 0;
	ctx.base_len = ft_strlen(base);
	if (flags.dot)
		flags.zero = 0;
	ctx.l = get_unbr_cl(nbr, flags, base);
	ctx.zero_pad_len = 0;
	if (flags.dot && flags.precision > ft_get_unbr_size(nbr, base))
		ctx.zero_pad_len = flags.precision - ft_get_unbr_size(nbr, base);
	if (flags.zero && !flags.minus && flags.width > ctx.l)
	{
		ctx.zero_pad_len = flags.width - ctx.l;
		flags.width = 0;
	}
	ft_handle_padding(flags, ctx.l, &ctx.i);
	if (nbr != 0)
		ft_handle_hash(flags, base, ctx.base_len, &ctx.i);
	ft_putnchar('0', ctx.zero_pad_len, &ctx.i);
	if (!(nbr == 0 && flags.dot && flags.precision == 0))
		ft_putnbr_base(nbr, base, &ctx.i);
	ft_handle_justify(flags, ctx.l, &ctx.i);
	return (ctx.i);
}

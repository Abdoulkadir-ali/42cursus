/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:51:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hex_prefix(t_flags *flags, unsigned long n)
{
	if (flags->hash && n != 0)
	{
		if (flags->type == 'x')
		{
			ft_putstr_fd("0x", flags->fd);
			return (2);
		}
		else if (flags->type == 'X')
		{
			ft_putstr_fd("0X", flags->fd);
			return (2);
		}
	}
	return (0);
}

static void	ft_calc_hex_params(unsigned long n, t_flags *flags, int *num_len,
		int *total_len)
{
	*num_len = ft_count_hex_digits(n);
	if (flags->has_precision && flags->precision == 0 && n == 0)
		*num_len = 0;
	*total_len = *num_len;
	if (flags->has_precision && flags->precision > *num_len)
		*total_len = flags->precision;
	if (flags->hash && n != 0)
		*total_len += 2;
}

int	ft_print_hex_with_flags(unsigned long n, t_flags *flags)
{
	int			count;
	int			num_len;
	int			total_len;
	const char	*base;

	base = "0123456789abcdef";
	if (flags->type == 'X')
		base = "0123456789ABCDEF";
	ft_calc_hex_params(n, flags, &num_len, &total_len);
	count = 0;
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, flags->zero, 0,
				flags->fd);
	count += ft_print_hex_prefix(flags, n);
	if (flags->has_precision)
		count += ft_print_precision_zeros(ft_count_hex_digits(n),
				flags->precision, flags->fd);
	if (!(flags->has_precision && flags->precision == 0 && n == 0))
		count += ft_putunbr_base(n, base, flags->fd);
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	return (count);
}

int	ft_handle_hex(va_list args, t_flags *flags)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_print_hex_with_flags(n, flags));
}

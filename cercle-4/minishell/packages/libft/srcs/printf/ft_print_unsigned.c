/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:52:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:57:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_unsigned_prefix(t_flags *flags, int total_len)
{
	int	count;

	count = 0;
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, flags->zero, 0,
				flags->fd);
	return (count);
}

int	ft_print_unsigned_number_part(unsigned int n, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->has_precision)
		count += ft_print_precision_zeros(ft_count_digits(n), flags->precision,
				flags->fd);
	if (!(flags->has_precision && flags->precision == 0 && n == 0))
		count += ft_putunbr_base(n, "0123456789", flags->fd);
	return (count);
}

int	ft_print_unsigned_suffix(t_flags *flags, int total_len)
{
	int	count;

	count = 0;
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	return (count);
}

int	ft_print_unsigned_with_flags(unsigned int n, t_flags *flags)
{
	int	count;
	int	num_len;
	int	total_len;

	num_len = ft_count_digits(n);
	if (flags->has_precision && flags->precision == 0 && n == 0)
		num_len = 0;
	total_len = num_len;
	if (flags->has_precision && flags->precision > num_len)
		total_len = flags->precision;
	count = ft_print_unsigned_prefix(flags, total_len);
	count += ft_print_unsigned_number_part(n, flags);
	count += ft_print_unsigned_suffix(flags, total_len);
	return (count);
}

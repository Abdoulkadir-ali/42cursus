/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_signed.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:52:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:57:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_calc_number_params(long n, t_flags *flags, int *num_len,
		int *total_len)
{
	long	tmp;

	tmp = n;
	if (n < 0)
		tmp = -n;
	*num_len = ft_count_digits(tmp);
	if (flags->has_precision && flags->precision == 0 && n == 0)
		*num_len = 0;
	*total_len = *num_len;
	if (flags->has_precision && flags->precision > *num_len)
		*total_len = flags->precision;
	if (n < 0 || flags->plus || flags->space)
		(*total_len)++;
}

int	ft_print_prefix(long n, t_flags *flags, int total_len)
{
	int	count;
	int	sign_printed;

	count = 0;
	if (flags->zero && !flags->minus && flags->width > total_len)
		count += ft_print_sign_and_prefix(n, flags, &sign_printed);
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, flags->zero, 0,
				flags->fd);
	if (!flags->zero || flags->minus || flags->width <= total_len)
		count += ft_print_sign_and_prefix(n, flags, &sign_printed);
	return (count);
}

int	ft_print_number_part(long tmp, long n, t_flags *flags)
{
	int	count;

	count = 0;
	if (flags->has_precision)
		count += ft_print_precision_zeros(ft_count_digits(tmp),
				flags->precision, flags->fd);
	if (!(flags->has_precision && flags->precision == 0 && n == 0))
		count += ft_putunbr_base(tmp, "0123456789", flags->fd);
	return (count);
}

int	ft_print_suffix(t_flags *flags, int total_len)
{
	int	count;

	count = 0;
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	return (count);
}

int	ft_print_number_with_flags(long n, t_flags *flags)
{
	int		count;
	int		num_len;
	int		total_len;
	long	tmp;

	ft_calc_number_params(n, flags, &num_len, &total_len);
	tmp = n;
	if (n < 0)
		tmp = -n;
	count = ft_print_prefix(n, flags, total_len);
	count += ft_print_number_part(tmp, n, flags);
	count += ft_print_suffix(flags, total_len);
	return (count);
}

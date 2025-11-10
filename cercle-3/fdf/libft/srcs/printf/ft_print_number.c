/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 10:53:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static void	ft_calc_number_params(long n, t_flags *flags, int *num_len,
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

int	ft_print_number_with_flags(long n, t_flags *flags)
{
	int		count;
	int		num_len;
	int		total_len;
	int		sign_printed;
	long	tmp;

	ft_calc_number_params(n, flags, &num_len, &total_len);
	tmp = n;
	if (n < 0)
		tmp = -n;
	count = 0;
	if (flags->zero && !flags->minus && flags->width > total_len)
		count += ft_print_sign_and_prefix(n, flags, &sign_printed);
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, flags->zero, 0);
	if (!flags->zero || flags->minus || flags->width <= total_len)
		count += ft_print_sign_and_prefix(n, flags, &sign_printed);
	if (flags->has_precision)
		count += ft_print_precision_zeros(ft_count_digits(tmp),
				flags->precision);
	if (!(flags->has_precision && flags->precision == 0 && n == 0))
		count += ft_putunbr_base(tmp, "0123456789");
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0);
	return (count);
}

int	ft_print_unsigned_with_flags(unsigned int n, t_flags *flags)
{
	int		count;
	int		num_len;
	int		total_len;

	num_len = ft_count_digits(n);
	if (flags->has_precision && flags->precision == 0 && n == 0)
		num_len = 0;
	total_len = num_len;
	if (flags->has_precision && flags->precision > num_len)
		total_len = flags->precision;
	count = 0;
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, flags->zero, 0);
	if (flags->has_precision)
		count += ft_print_precision_zeros(ft_count_digits(n),
				flags->precision);
	if (!(flags->has_precision && flags->precision == 0 && n == 0))
		count += ft_putunbr_base(n, "0123456789");
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0);
	return (count);
}

int	ft_handle_number(va_list args, t_flags *flags)
{
	long			n;
	unsigned int	u;

	if (flags->type == 'd' || flags->type == 'i')
	{
		n = (long)va_arg(args, int);
		return (ft_print_number_with_flags(n, flags));
	}
	else if (flags->type == 'u')
	{
		u = va_arg(args, unsigned int);
		return (ft_print_unsigned_with_flags(u, flags));
	}
	return (0);
}

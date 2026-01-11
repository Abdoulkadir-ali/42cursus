/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 13:16:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle_null_pointer(t_flags *flags)
{
	int	count;
	int	total_len;

	total_len = 5;
	count = 0;
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	ft_putstr_fd("(nil)", flags->fd);
	count += 5;
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	return (count);
}

int	ft_handle_pointer(va_list args, t_flags *flags)
{
	unsigned long	ptr;
	int				count;
	int				num_len;
	int				total_len;

	ptr = (unsigned long)va_arg(args, void *);
	count = 0;
	if (!ptr)
		return (ft_handle_null_pointer(flags));
	num_len = ft_count_hex_digits(ptr);
	total_len = num_len + 2;
	if (!flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	ft_putstr_fd("0x", flags->fd);
	count += 2 + ft_putunbr_base(ptr, "0123456789abcdef", flags->fd);
	if (flags->minus && flags->width > total_len)
		count += ft_print_width(flags->width - total_len, 0, 0, flags->fd);
	return (count);
}

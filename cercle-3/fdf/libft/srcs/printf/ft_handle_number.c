/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 10:51:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_print_sign_and_prefix(long n, t_flags *flags, int *sign_printed)
{
	int	count;

	count = 0;
	*sign_printed = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		count++;
		*sign_printed = 1;
	}
	else if (flags->plus)
	{
		ft_putchar_fd('+', 1);
		count++;
		*sign_printed = 1;
	}
	else if (flags->space)
	{
		ft_putchar_fd(' ', 1);
		count++;
		*sign_printed = 1;
	}
	return (count);
}

int	ft_print_precision_zeros(int num_len, int precision)
{
	int	count;

	count = 0;
	while (num_len < precision)
	{
		ft_putchar_fd('0', 1);
		count++;
		num_len++;
	}
	return (count);
}

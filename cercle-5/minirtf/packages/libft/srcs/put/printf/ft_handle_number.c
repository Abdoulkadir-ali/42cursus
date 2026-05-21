/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 13:20:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Executes public ft_print_sign_and_prefix utility.
 * @note Public library exported function.
 */
int	ft_print_sign_and_prefix(long n, t_flags *flags, int *sign_printed)
{
	int	count;

	count = 0;
	*sign_printed = 0;
	if (n < 0)
	{
		ft_putchar_fd('-', flags->fd);
		count++;
		*sign_printed = 1;
	}
	else if (flags->plus)
	{
		ft_putchar_fd('+', flags->fd);
		count++;
		*sign_printed = 1;
	}
	else if (flags->space)
	{
		ft_putchar_fd(' ', flags->fd);
		count++;
		*sign_printed = 1;
	}
	return (count);
}

/**
 * @brief Evaluates if input satisfies ft_print_precision_zeros condition.
 * @note Public library exported function.
 */
int	ft_print_precision_zeros(int num_len, int precision, int fd)
{
	int	count;

	count = 0;
	while (num_len < precision)
	{
		ft_putchar_fd('0', fd);
		count++;
		num_len++;
	}
	return (count);
}

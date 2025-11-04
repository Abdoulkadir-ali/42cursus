/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 11:26:15 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/24 11:41:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_count_digits(long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

static int	ft_count_udigits(unsigned int n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	while (n > 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

int	ft_handle_char(va_list args)
{
	ft_putchar_fd(va_arg(args, int), 1);
	return (1);
}

int	ft_handle_string(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_handle_number(va_list args, char format)
{
	int				n;
	unsigned int	u;
	int				count;

	if (format == 'd' || format == 'i')
	{
		n = va_arg(args, int);
		ft_putnbr_fd(n, 1);
		count = ft_count_digits(n);
	}
	else if (format == 'u')
	{
		u = va_arg(args, unsigned int);
		ft_putunbr_fd(u, 1);
		count = ft_count_udigits(u);
	}
	else
		count = 0;
	return (count);
}

int	ft_handle_hex(va_list args, char format)
{
	unsigned int	n;
	int				count;

	n = va_arg(args, unsigned int);
	if (format == 'x')
		count = ft_putunbr_base(n, "0123456789abcdef");
	else if (format == 'X')
		count = ft_putunbr_base(n, "0123456789ABCDEF");
	else
		count = 0;
	return (count);
}

int	ft_handle_pointer(va_list args)
{
	unsigned long ptr;
	int count;

	ptr = (unsigned long)va_arg(args, void *);
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	count = 2 + ft_putunbr_base(ptr, "0123456789abcdef");
	return (count);
}
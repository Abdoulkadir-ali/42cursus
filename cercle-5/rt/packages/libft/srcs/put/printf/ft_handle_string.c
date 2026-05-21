/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:50:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Calculates the print length for a null string.
 * @note Public library exported function.
 */
static int	ft_get_null_print_len(t_flags *flags, int *len)
{
	if (flags->has_precision && flags->precision < 6)
		return (0);
	*len = 6;
	if (flags->has_precision && flags->precision < *len)
		return (flags->precision);
	return (*len);
}

/**
 * @brief Calculates the print length for a string.
 * @note Public library exported function.
 */
static int	ft_get_print_len(char **str, t_flags *flags)
{
	int	len;
	int	print_len;

	if (!*str)
	{
		print_len = ft_get_null_print_len(flags, &len);
		if (print_len > 0)
			*str = "(null)";
		return (print_len);
	}
	len = ft_strlen(*str);
	print_len = len;
	if (flags->has_precision && flags->precision < len)
		print_len = flags->precision;
	return (print_len);
}

/**
 * @brief Performs string manipulation or inspection.
 * @note Public library exported function.
 */
int	ft_print_string_with_flags(char *str, t_flags *flags)
{
	int	count;
	int	print_len;

	print_len = ft_get_print_len(&str, flags);
	count = 0;
	if (flags->minus)
	{
		if (str)
			write(flags->fd, str, print_len);
		count = print_len + ft_print_width(flags->width - print_len, 0, 0,
				flags->fd);
	}
	else
	{
		count = ft_print_width(flags->width - print_len, 0, 0, flags->fd);
		if (str)
			write(flags->fd, str, print_len);
		count += print_len;
	}
	return (count);
}

/**
 * @brief Performs string manipulation or inspection.
 * @note Public library exported function.
 */
int	ft_handle_string(va_list args, t_flags *flags)
{
	char	*str;

	str = va_arg(args, char *);
	return (ft_print_string_with_flags(str, flags));
}

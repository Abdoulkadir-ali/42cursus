/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 07:12:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/08 07:12:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list args;
	size_t i;
	size_t count;
	int error;

	va_start(args, str);
	error = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			count += ft_handle_flags(str, &i, args, &error);
			if (error)
			{
				va_end(args);
				return (-1);
			}
		}
		else
		{
			ft_putchar(str[i++]);
			count++;
		}
	}
	va_end(args);
	return (count);
}

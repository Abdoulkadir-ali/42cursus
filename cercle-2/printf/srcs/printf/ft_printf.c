/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:35:09 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/28 15:35:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_printf(const char *str, ...)
{
	va_list	args;
	size_t	i;
	size_t	count;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
			count += ft_handle_flags(str, &i, args);
		else
		{
			ft_putchar(str[i++]);
			count++;
		}
	}
	va_end(args);
	return (count);
}

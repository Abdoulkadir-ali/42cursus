/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handlers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/11/28 15:35:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/28 15:35:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


static size_t	dispatch_handler(char c, t_flags flags, va_list args)
{
	if (c == 'c')
		return (ft_handle_char(flags, (char)va_arg(args, int)));
	else if (c == '%')
		return (ft_handle_percent());
	else if (c == 's')
		return (ft_handle_str(flags, va_arg(args, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_handle_nbr(flags, args, "0123456789"));
	else if (c == 'u')
		return (ft_handle_unbr(flags, get_unsigned_nbr(flags, args),
				"0123456789"));
	else if (c == 'x')
		return (ft_handle_unbr(flags, get_unsigned_nbr(flags, args),
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_handle_unbr(flags, get_unsigned_nbr(flags, args),
				"0123456789ABCDEF"));
	else if (c == 'p')
		return (ft_handle_ptr(flags, va_arg(args, void *)));
	return (0);
}

size_t	ft_handle_flags(const char *str, size_t *i, va_list args, int *error)
{
	t_flags flags;

	(*i)++;
	flags = (t_flags){0};
	ft_build_flags(&flags, str, i, args);
	if (flags.error)
	{
		*error = 1;
		return (0);
	}
	return (dispatch_handler(str[(*i)++], flags, args));
}

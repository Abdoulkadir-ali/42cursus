/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:50:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 23:00:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_error(char *format, ...)
{
	va_list args;

	if (!format)
		return (-1);
	va_start(args, format);
	ft_vprintf_fd(2, format, args);
	va_end(args);
	return (1);
}
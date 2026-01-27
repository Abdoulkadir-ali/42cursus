/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_number.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:52:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 19:56:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

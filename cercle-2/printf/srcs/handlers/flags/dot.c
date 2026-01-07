/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 15:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_apply_precision(size_t l, t_flags flags, size_t num_digits)
{
	if (flags.dot)
	{
		if (flags.precision > l)
			l = flags.precision;
		if (num_digits == 0 && flags.precision == 0)
			l = 0;
	}
	return (l);
}

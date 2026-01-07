/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 15:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_hash(t_flags flags, const char *base, size_t l, size_t *i)
{
	if (flags.hash && l == 16)
	{
		ft_putnchar('0', 1, i);
		if (base[10] == 'A')
			ft_putnchar('X', 1, i);
		else
			ft_putnchar('x', 1, i);
	}
}

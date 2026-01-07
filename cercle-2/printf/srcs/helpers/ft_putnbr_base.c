/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:18:05 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/29 20:18:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(size_t nb, const char *base, size_t *i)
{
	size_t	base_len;

	base_len = ft_strlen(base);
	if (nb >= base_len)
		ft_putnbr_base(nb / base_len, base, i);
	ft_putchar(base[nb % base_len]);
	(*i)++;
}

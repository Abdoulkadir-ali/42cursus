/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 20:56:49 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/29 20:56:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_handle_padding(t_flags flags, size_t l, size_t *i)
{
	size_t	pad_len;
	char	c;

	pad_len = 0;
	if (flags.width > 0 && flags.width > l)
		pad_len = flags.width - l;
	c = ft_get_pad_char(flags);
	if (pad_len > 0 && !flags.minus)
		ft_putnchar(c, pad_len, i);
}

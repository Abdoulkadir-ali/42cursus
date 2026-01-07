/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:21:20 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 16:21:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_handle_char(t_flags flags, const char c)
{
	size_t	i;
	t_flags	local_flags;

	local_flags = flags;
	local_flags.zero = 0;
	i = 0;
	ft_handle_padding(local_flags, 1, &i);
	ft_putchar(c);
	ft_handle_justify(local_flags, 1, &i);
	return (i + 1);
}

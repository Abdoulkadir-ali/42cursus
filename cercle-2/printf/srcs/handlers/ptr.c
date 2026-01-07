/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 16:21:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 16:21:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_handle_ptr(t_flags flags, void *ptr)
{
	t_flags	local_flags;

	local_flags = flags;
	local_flags.zero = 0;
	local_flags.dot = 0;
	local_flags.precision = 0;
	if (!ptr)
		return (ft_handle_str(local_flags, "(nil)"));
	local_flags.hash = 1;
	return (ft_handle_unbr(local_flags, (size_t)ptr, "0123456789abcdef"));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:29:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	ft_print_debug(const char *fmt, ...)
{
	va_list	ap;

	if (!DEBUG)
		return ;
	va_start(ap, fmt);
	printf("[DEBUG]: ");
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

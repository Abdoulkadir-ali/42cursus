/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 03:30:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 03:33:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdarg.h>

void	debug_printf(const char *format, ...)
{
#if DEBUG
	va_list	args;

	va_start(args, format);
	vprintf(format, args);
	va_end(args);
#else
	(void)format;
#endif
}

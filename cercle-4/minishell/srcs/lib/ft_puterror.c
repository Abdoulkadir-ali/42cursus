/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:32:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 00:23:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_puterror(const char *fmt, ...)
{
	va_list	args;

	ft_putstr_fd("minishell: ", 2);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

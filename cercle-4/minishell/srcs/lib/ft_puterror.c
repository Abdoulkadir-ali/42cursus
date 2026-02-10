/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:32:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 23:00:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_puterror(const char *fmt, ...)
{
	va_list	args;

	fprintf(stderr, "minishell: ");
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
}

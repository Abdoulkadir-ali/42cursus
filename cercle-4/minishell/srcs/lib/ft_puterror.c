/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:32:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/12 19:26:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	ft_puterror(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	ft_vputerror_header_fd(2, "minishell", fmt, args);
	va_end(args);
}
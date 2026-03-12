/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                                            */
/*   Created: 2026/03/12 18:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/12 18:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_vputerror_fd(int fd, const char *fmt, va_list args)
{
	ft_vprintf_fd(fd, fmt, args);
}

void	ft_vputerror_header_fd(int fd, const char *header, const char *fmt,
		va_list args)
{
	if (header)
	{
		ft_putstr_fd((char *)header, fd);
		ft_putstr_fd(": ", fd);
	}
	ft_vputerror_fd(fd, fmt, args);
}

void	ft_puterror_fmt(const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	ft_vputerror_fd(2, fmt, args);
	va_end(args);
}

void	ft_puterror_header(const char *header, const char *fmt, ...)
{
	va_list	args;

	va_start(args, fmt);
	ft_vputerror_header_fd(2, header, fmt, args);
	va_end(args);
}

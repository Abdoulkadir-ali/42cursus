/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:12:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 02:08:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"

void	ft_puterror(const char *message)
{
	if (message)
		ft_putendl_fd((char *)message, 2);
}

void	print_error(const char *msg, ...)
{
	va_list	args;

	if (msg)
	{
		va_start(args, msg);
		ft_vprintf_fd(2, msg, args);
		va_end(args);
		ft_putchar_fd('\n', 2);
	}
}

void	safe_exit(const char *msg, t_app *app, int code, ...)
{
	va_list	args;

	if (msg)
	{
		if (code != 0)
			ft_putstr_fd("Error: ", 2);
		va_start(args, code);
		ft_vprintf_fd(2, msg, args);
		va_end(args);
		ft_putchar_fd('\n', 2);
	}
	cleanup_app(app);
	exit(code);
}

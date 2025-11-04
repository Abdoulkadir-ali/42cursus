/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/10/24 11:28:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);

/* Handler functions */
int	ft_handle_char(va_list args);
int	ft_handle_string(va_list args);
int	ft_handle_number(va_list args, char format);
int	ft_handle_hex(va_list args, char format);
int	ft_handle_pointer(va_list args);

#endif
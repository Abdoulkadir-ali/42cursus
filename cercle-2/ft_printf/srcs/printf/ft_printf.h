/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/04 10:54:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft/libft.h"
# include <stdarg.h>
# include <unistd.h>

/* Flags structure for bonus handling */
typedef struct s_flags
{
	int		minus;
	int		zero;
	int		hash;
	int		space;
	int		plus;
	int		width;
	int		precision;
	int		has_precision;
	char	type;
}	t_flags;

int	ft_printf(const char *format, ...);

/* Handler functions */
int	ft_handle_char(va_list args, t_flags *flags);
int	ft_handle_string(va_list args, t_flags *flags);
int	ft_handle_number(va_list args, t_flags *flags);
int	ft_handle_hex(va_list args, t_flags *flags);
int	ft_handle_pointer(va_list args, t_flags *flags);

/* Flag parsing and handling */
int	ft_parse_flags(const char *format, int *i, t_flags *flags);
int	ft_print_width(int width, int zero, int left);
int	ft_count_digits(long n);
int	ft_count_hex_digits(unsigned long n);
int	ft_print_number_with_flags(long n, t_flags *flags);
int	ft_print_unsigned_with_flags(unsigned int n, t_flags *flags);
int	ft_print_hex_with_flags(unsigned long n, t_flags *flags);
int	ft_print_string_with_flags(char *str, t_flags *flags);
int	ft_print_sign_and_prefix(long n, t_flags *flags, int *sign_printed);
int	ft_print_precision_zeros(int num_len, int precision);

#endif
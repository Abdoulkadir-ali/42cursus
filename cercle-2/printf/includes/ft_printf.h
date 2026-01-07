/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 21:59:38 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/30 21:59:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define LEN_NONE 0
# define LEN_L 1
# define LEN_LL 2
# define LEN_H 3
# define LEN_HH 4

typedef struct s_flags
{
	size_t		hash;
	size_t		space;
	size_t		dot;
	size_t		plus;
	size_t		minus;
	size_t		zero;
	size_t		precision;
	size_t		width;
	size_t		length;
}				t_flags;

typedef struct s_nbr_ctx
{
	size_t		i;
	int			sign;
	char		sign_c;
	size_t		nb;
	size_t		num_digits;
	size_t		l;
	size_t		total_len;
	size_t		pad_len;
}				t_nbr_ctx;

typedef struct s_unbr_ctx
{
	size_t		i;
	size_t		l;
	size_t		zero_pad_len;
	size_t		base_len;
}				t_unbr_ctx;

typedef struct s_str_ctx
{
	size_t		i;
	size_t		l;
	t_flags		local_flags;
	const char	*tmp;
}				t_str_ctx;

char			*ft_strchr(const char *s, int c);
void			ft_putchar(char c);
void			ft_putnbr_base(size_t nb, const char *base, size_t *i);
void			ft_putstr(const char *str);
size_t			ft_putnstr(const char *str, size_t n);
void			ft_putnchar(char c, size_t n, size_t *count);
int				ft_atoi(const char *str, size_t *i);

void			ft_parse_length(const char *str, size_t *i, t_flags *flags);
void			ft_parse_precision(const char *str, size_t *i, va_list args,
					t_flags *flags);
void			ft_parse_width(const char *str, size_t *i, va_list args,
					t_flags *flags);
size_t			ft_handle_char(t_flags flags, const char c);
size_t			ft_handle_flags(const char *str, size_t *i, va_list args);
size_t			ft_handle_nbr(t_flags flags, va_list args, const char *base);
size_t			ft_handle_ptr(t_flags flags, void *ptr);
size_t			ft_handle_str(t_flags flags, const char *str);
size_t			ft_handle_percent(void);
size_t			ft_handle_unbr(t_flags flags, size_t nbr, const char *base);
size_t			get_unsigned_nbr(t_flags flags, va_list args);
void			ft_handle_padding(t_flags flags, size_t cl, size_t *i);
void			ft_handle_justify(t_flags flags, size_t cl, size_t *i);
int				ft_isdigit(int c);
size_t			ft_strlen(const char *str);
t_flags			ft_build_flags(const char *str, size_t *i, va_list args);
void			ft_handle_sign(const char sign_c, size_t *i);
void			ft_handle_hash(t_flags flags, const char *base, size_t l,
					size_t *i);
char			ft_get_pad_char(t_flags flags);
size_t			ft_apply_precision(size_t cl, t_flags flags, size_t num_digits);
int				ft_isdigit(int c);
size_t			ft_printf(const char *str, ...);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 23:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	add_char(char *str, size_t size, size_t pos, char c)
{
	if (pos < size - 1)
		str[pos] = c;
	return (pos + 1);
}

static size_t	add_str(char *str, size_t size, size_t pos, const char *s)
{
	if (!s)
		s = "(null)";
	while (*s)
	{
		pos = add_char(str, size, pos, *s);
		s++;
	}
	return (pos);
}

static size_t	add_num(char *str, size_t size, size_t pos, int n)
{
	char	*tmp;

	tmp = ft_itoa(n);
	if (!tmp)
		return (pos);
	pos = add_str(str, size, pos, tmp);
	free(tmp);
	return (pos);
}

int	ft_vsnprintf(char *str, size_t size, const char *format, va_list args)
{
	size_t	i;
	size_t	pos;

	i = 0;
	pos = 0;
	if (size == 0)
		return (0);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				pos = add_str(str, size, pos, va_arg(args, char *));
			else if (format[i] == 'd' || format[i] == 'i')
				pos = add_num(str, size, pos, va_arg(args, int));
			else if (format[i] == 'c')
				pos = add_char(str, size, pos, (char)va_arg(args, int));
			else if (format[i] == '%')
				pos = add_char(str, size, pos, '%');
		}
		else
			pos = add_char(str, size, pos, format[i]);
		i++;
	}
	if (pos < size)
		str[pos] = '\0';
	else
		str[size - 1] = '\0';
	return ((int)pos);
}

int	ft_snprintf(char *str, size_t size, const char *format, ...)
{
	va_list	args;
	int		res;

	va_start(args, format);
	res = ft_vsnprintf(str, size, format, args);
	va_end(args);
	return (res);
}

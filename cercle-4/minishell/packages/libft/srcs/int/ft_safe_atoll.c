/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:05 by abdali            #+#    #+#             */
/*   Updated: 2026/01/26 14:07:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign_and_skip_spaces(const char **str_ptr)
{
	int	sign;

	sign = 1;
	while (**str_ptr == ' ' || (**str_ptr >= 9 && **str_ptr <= 13))
		(*str_ptr)++;
	if (**str_ptr == '-')
	{
		sign = -1;
		(*str_ptr)++;
	}
	else if (**str_ptr == '+')
		(*str_ptr)++;
	return (sign);
}

static int	parse_number(const char **str_ptr, unsigned long long *res,
		unsigned long long max_val, int *error)
{
	int	count;

	*res = 0;
	count = 0;
	while (**str_ptr && ft_isdigit(**str_ptr))
	{
		*res = *res * 10 + (**str_ptr - '0');
		if (*res > max_val)
		{
			*error = 1;
			return (0);
		}
		(*str_ptr)++;
		count++;
	}
	return (count);
}

long long	ft_safe_atoll(const char *str, long long MAX, int *error,
		char **endptr)
{
	int					sign;
	unsigned long long	res;
	int					count;

	if (error)
		*error = 0;
	sign = get_sign_and_skip_spaces(&str);
	if (sign == -1)
		MAX += 1;
	count = parse_number(&str, &res, MAX, error);
	if (endptr)
		*endptr = (char *)str;
	if (*error || count == 0)
	{
		if (error)
			*error = 1;
		return (0);
	}
	return ((long long)res * sign);
}

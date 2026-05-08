/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:05 by abdali            #+#    #+#             */
/*   Updated: 2026/05/08 03:13:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Gets the sign of the number and skips leading whitespace.
 * @note Internal helper function.
 */
static int	get_sign_and_skip_spaces(const char **str_ptr)
{
	int	sign;

	sign = 1;
	*str_ptr = ft_skip_spaces(*str_ptr);
	if (**str_ptr == '-')
	{
		sign = -1;
		(*str_ptr)++;
	}
	else if (**str_ptr == '+')
		(*str_ptr)++;
	return (sign);
}

/**
 * @brief Parses the number from the string, checking for overflow.
 * @note Internal helper function.
 */
static int	parse_number(const char **s, unsigned long long *res,
		unsigned long long max_val, bool *err)
{
	int	count;

	*res = 0;
	count = 0;
	while (**s && ft_isdigit(**s))
	{
		*res = *res * 10 + (**s - '0');
		if (*res > max_val)
		{
			*err = true;
			return (0);
		}
		(*s)++;
		count++;
	}
	while (**s)
	{
		if (!ft_isspace(**s))
			*err = true;
		(*s)++;
	}
	return (count);
}

/**
 * @brief Converts a string to a long long safely, checking for overflow.
 * 
 * @param str Target structural variable.
 * @param error Target structural variable.
 * @return long long output natively.
 */
long long	ft_safe_atoll(const char *str, bool *error)
{
	int					sign;
	unsigned long long	res;
	int					count;
	unsigned long long	max;

	if (error)
		*error = false;
	sign = get_sign_and_skip_spaces(&str);
	max = LLONG_MAX;
	if (sign == -1)
		max += 1;
	count = parse_number(&str, &res, max, error);
	if (*error || count == 0)
	{
		if (error)
			*error = true;
		return (0);
	}
	return ((long long)res * sign);
}

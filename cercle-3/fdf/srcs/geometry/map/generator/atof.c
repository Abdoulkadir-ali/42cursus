/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Parse an optional sign prefix.
 * @param str Pointer to the current parse cursor.
 * @return Parsed sign as `1` or `-1`.
 */
static int	parse_sign(const char **str)
{
	int	sign;

	sign = 1;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

/**
 * @brief Parse the integer component of a decimal string.
 * @param str Pointer to the current parse cursor.
 * @return Parsed integer value as a double.
 */
static double	parse_integer(const char **str)
{
	double	num;

	num = 0;
	while (**str >= '0' && **str <= '9')
	{
		num = num * 10 + (**str - '0');
		(*str)++;
	}
	return (num);
}

/**
 * @brief Parse the fractional component of a decimal string.
 * @param str Pointer to the current parse cursor.
 * @return Parsed fractional value.
 */
static double	parse_fraction(const char **str)
{
	double	num;
	double	div;

	num = 0;
	div = 1;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			num = num * 10 + (**str - '0');
			div *= 10;
			(*str)++;
		}
	}
	return (num / div);
}

/**
 * @brief Convert a string to an integer with null safety.
 * @param str String to parse.
 * @return Parsed integer value, or `0` for a null string.
 */
int	ft_atoi_safe(const char *str)
{
	if (!str)
		return (0);
	return (ft_atoi(str));
}

/**
 * @brief Convert a decimal string into a floating-point value.
 * @param str String to parse.
 * @return Parsed floating-point value.
 */
float	ft_atof(const char *str)
{
	int		sign;
	double	integer;
	double	fraction;

	sign = parse_sign(&str);
	integer = parse_integer(&str);
	fraction = parse_fraction(&str);
	return (sign * (integer + fraction));
}

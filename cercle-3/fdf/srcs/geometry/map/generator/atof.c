/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atof.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:18:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

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

int	ft_atoi_safe(const char *str)
{
	if (!str)
		return (0);
	return (ft_atoi(str));
}

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

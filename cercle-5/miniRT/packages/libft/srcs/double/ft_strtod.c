/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:40:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 06:48:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_strtod(const char *s)
{
	const char *p = s;
	int sign = 1;
	double val = 0.0;

	if (!p)
		return (0.0);
	while (*p && ft_isspace(*p))
		p++;
	if (*p == '+' || *p == '-')
	{
		if (*p == '-')
			sign = -1;
		p++;
	}
	while (*p && ft_isdigit(*p))
	{
		val = val * 10.0 + (double)(*p - '0');
		p++;
	}
	if (*p == '.')
	{
		double place = 0.1;
		p++;
		while (*p && ft_isdigit(*p))
		{
			val += (double)(*p - '0') * place;
			place *= 0.1;
			p++;
		}
	}
	if (*p == 'e' || *p == 'E')
	{
		int exp_sign = 1;
		int exp = 0;
		p++;
		if (*p == '+' || *p == '-')
		{
			if (*p == '-')
				exp_sign = -1;
			p++;
		}
		while (*p && ft_isdigit(*p))
		{
			exp = exp * 10 + (*p - '0');
			p++;
		}
		val *= pow(10.0, (double)(exp_sign * exp));
	}
	return (sign * val);
}


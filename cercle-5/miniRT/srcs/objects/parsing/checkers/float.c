/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 23:05:28 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 16:32:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_valid_float(const char *s)
{
	size_t	i;
	size_t	dot;

	i = 0;
	dot = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i] || (s[i] == '.' && !s[i + 1]))
		return (false);
	while (s[i])
	{
		if (s[i] == '.')
		{
			dot++;
			if (dot > 1 || !ft_isdigit(s[i + 1]))
				return (false);
		}
		else if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

double	parse_float(const char *s)
{
	double	res;

	if (!s || !is_valid_float((char *)s))
		return (0.0);
	res = ft_strtod((char *)s);
	return (res);
}

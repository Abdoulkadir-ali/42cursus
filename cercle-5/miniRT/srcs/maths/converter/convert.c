/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 06:51:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:10:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

double	*to_double(const char *s)
{
	double	*v;

	v = malloc(sizeof(double));
	if (!v)
		return (NULL);
	*v = ft_strtod(s);
	return (v);
}

float	*to_float(const char *s)
{
	float	*v;

	v = malloc(sizeof(float));
	if (!v)
		return (NULL);
	*v = ft_strtof(s);
	return (v);
}

int	*to_int(const char *s)
{
	int	*v;

	v = malloc(sizeof(int));
	if (!v)
		return (NULL);
	*v = ft_atoi(s);
	return (v);
}

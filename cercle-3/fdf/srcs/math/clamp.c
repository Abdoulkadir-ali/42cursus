/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:02 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 22:43:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"

void	clamp_float(float *value, float min, float max)
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

void	clamp_double(double *value, double min, double max)
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

void	clamp_uint(unsigned int *value, unsigned int min, unsigned int max)
{
	if (*value < min)
		*value = min;
	if (*value > max)
		*value = max;
}

int	clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

double	clamp_d(double value, double min, double max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

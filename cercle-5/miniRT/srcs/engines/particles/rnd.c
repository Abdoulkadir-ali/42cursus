/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rnd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "particles.h"

double	rnd01(unsigned int *seed)
{
	*seed = *seed * 1664525u + 1013904223u;
	return ((double)(*seed >> 1) / 2147483648.0);
}

double	rnd_range(double lo, double hi, unsigned int *seed)
{
	return (lo + (hi - lo) * rnd01(seed));
}

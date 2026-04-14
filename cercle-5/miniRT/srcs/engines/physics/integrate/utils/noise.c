/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include <math.h>

static double	lattice_val(int ix, int iy, int iz)
{
	unsigned int	h;

	h = (unsigned int)ix * 1664525u + 1013904223u;
	h ^= (unsigned int)iy * 22695477u + 1u;
	h ^= (unsigned int)iz * 134775813u + 1u;
	h = (h ^ (h >> 16)) * 0x45d9f3bu;
	h = (h ^ (h >> 16)) * 0x45d9f3bu;
	h ^= h >> 16;
	return ((double)(h & 0xffffu) / 32767.5 - 1.0);
}

static double	fade(double t)
{
	return (t * t * t * (t * (t * 6.0 - 15.0) + 10.0));
}

static double	lerp(double a, double b, double t)
{
	return (a + t * (b - a));
}

double	value_noise3(double x, double y, double z)
{
	int		i[3];
	double	f[3];
	double	l[3];
	double	c[8];

	i[0] = (int)floor(x);
	i[1] = (int)floor(y);
	i[2] = (int)floor(z);
	f[0] = x - (double)i[0];
	f[1] = y - (double)i[1];
	f[2] = z - (double)i[2];
	l[0] = fade(f[0]);
	l[1] = fade(f[1]);
	l[2] = fade(f[2]);
	c[0] = lattice_val(i[0], i[1], i[2]);
	c[1] = lattice_val(i[0] + 1, i[1], i[2]);
	c[2] = lattice_val(i[0], i[1] + 1, i[2]);
	c[3] = lattice_val(i[0] + 1, i[1] + 1, i[2]);
	c[4] = lattice_val(i[0], i[1], i[2] + 1);
	c[5] = lattice_val(i[0] + 1, i[1], i[2] + 1);
	c[6] = lattice_val(i[0], i[1] + 1, i[2] + 1);
	c[7] = lattice_val(i[0] + 1, i[1] + 1, i[2] + 1);
	return (lerp(lerp(lerp(c[0], c[1], l[0]), lerp(c[2], c[3], l[0]), l[1]),
			lerp(lerp(c[4], c[5], l[0]), lerp(c[6], c[7], l[0]), l[1]), l[2]));
}

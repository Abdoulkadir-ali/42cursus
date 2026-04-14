/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 22:03:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

/*
** Halton low-discrepancy sequence for sub-pixel jitter.
** base 2 for x, base 3 for y — standard TAA choice.
*/
static double	halton(size_t i, size_t base)
{
	double	f;
	double	r;

	f = 1.0;
	r = 0.0;
	while (i > 0)
	{
		f /= (double)base;
		r += f * (double)(i % base);
		i /= base;
	}
	return (r);
}

/* Precomputed LUT: halton(1..TAA_SEQ_LEN, base 2) and base 3.
** Same jitter for all pixels in a frame — compute once, lookup thereafter. */
static double	g_jx[TAA_SEQ_LEN];
static double	g_jy[TAA_SEQ_LEN];
static int		g_jitter_ready = 0;

static void	init_jitter_lut(void)
{
	size_t	i;

	i = 0;
	while (i < TAA_SEQ_LEN)
	{
		g_jx[i] = halton(i + 1, 2) - 0.5;
		g_jy[i] = halton(i + 1, 3) - 0.5;
		i++;
	}
	g_jitter_ready = 1;
}

/*
** Returns the jitter for frame index n in [-0.5, 0.5] NDC sub-pixel space.
*/
void	taa_get_jitter(size_t frame, double *jx, double *jy)
{
	if (!g_jitter_ready)
		init_jitter_lut();
	*jx = g_jx[frame % TAA_SEQ_LEN];
	*jy = g_jy[frame % TAA_SEQ_LEN];
}

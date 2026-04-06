/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   halton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 00:00:00 by abdoali          ###   ########.fr       */
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

/*
** Returns the jitter for frame index n in [-0.5, 0.5] NDC sub-pixel space.
*/
void	taa_get_jitter(size_t frame, double *jx, double *jy)
{
	size_t	idx;

	idx = (frame % TAA_SEQ_LEN) + 1;
	*jx = halton(idx, 2) - 0.5;
	*jy = halton(idx, 3) - 0.5;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:55:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

void	bin_objs(t_bin *bins, t_sah *s)
{
	size_t	i;
	int		b;

	i = 0;
	while (i < SAH_BINS)
	{
		aabb_reset(&bins[i].box);
		bins[i++].count = 0;
	}
	i = 0;
	while (i < s->n)
	{
		b = (int)((axis_val(s->centers[s->idx[i]], s->axis) - s->bmin) * s->k);
		if (b < 0)
			b = 0;
		if (b >= SAH_BINS)
			b = SAH_BINS - 1;
		aabb_union(&bins[b].box, &s->boxes[s->idx[i]]);
		bins[b].count++;
		i++;
	}
}

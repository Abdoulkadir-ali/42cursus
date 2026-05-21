/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sah.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:55:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	init_sah(t_sah *s, const t_aabb *boxes, const t_vec3 *centers,
				size_t *idx)
{
	t_aabb	cb;
	size_t	i;

	aabb_reset(&cb);
	i = 0;
	while (i < s->n)
		aabb_expand(&cb, centers[idx[i++]]);
	s->boxes = boxes;
	s->centers = centers;
	s->idx = idx;
	s->axis = pick_axis(cb, &s->k, &s->bmin);
}

int	sah_choose_axis(t_sah *s_in, t_sah_out *out)
{
	t_sah	s;
	t_bin	bins[SAH_BINS];
	float	cost;
	int		best;

	s.n = s_in->n;
	init_sah(&s, s_in->boxes, s_in->centers, s_in->idx);
	bin_objs(bins, &s);
	best = best_split(bins, &cost, &out->left, &out->right);
	if (best < 0)
		return (0);
	out->split = partition_idx(s, best);
	if (out->split <= 0 || out->split >= s.n)
		return (0);
	return (1);
}

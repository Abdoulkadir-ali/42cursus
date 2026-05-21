/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:00:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:00:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	fill_acc(t_bin *bins, t_split *s)
{
	t_aabb	acc;
	size_t	cc;
	int		i;

	aabb_reset(&acc);
	cc = 0;
	i = 0;
	while (i < SAH_BINS)
	{
		aabb_union(&acc, &bins[i].box);
		cc += bins[i].count;
		s->left[i] = acc;
		s->lc[i++] = cc;
	}
	aabb_reset(&acc);
	cc = 0;
	i = SAH_BINS - 1;
	while (i >= 0)
	{
		aabb_union(&acc, &bins[i].box);
		cc += bins[i].count;
		s->right[i] = acc;
		s->rc[i--] = cc;
	}
}

static void	check_cost(t_split *s, int i, float *out_cost, int *best)
{
	float	cost;

	cost = aabb_area(&s->left[i]) * s->lc[i]
		+ aabb_area(&s->right[i + 1]) * s->rc[i + 1];
	if (cost < *out_cost)
	{
		*out_cost = cost;
		*best = i;
	}
}

int	best_split(t_bin *bins, float *out_cost, t_aabb *lb, t_aabb *rb)
{
	t_split	s;
	int		i;
	int		best;

	fill_acc(bins, &s);
	best = -1;
	*out_cost = 1e30f;
	i = 0;
	while (i < SAH_BINS - 1)
	{
		if (s.lc[i] > 0 && s.rc[i + 1] > 0)
			check_cost(&s, i, out_cost, &best);
		i++;
	}
	if (best >= 0)
	{
		*lb = s.left[best];
		*rb = s.right[best + 1];
	}
	return (best);
}

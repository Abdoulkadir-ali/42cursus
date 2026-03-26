/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 07:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

extern bool	aabb_overlap_local(t_aabb a, t_aabb b);

/**
 * @brief Resolves Piège C: Inspects a single brick from Body A against all 
 * bricks of Body B. This removes the nested O(n*m) loop from a single function.
 */
static int	check_single_brick(t_body_pair *p, size_t ia, t_shape_pair *out, int c, int max)
{
	size_t	j;

	j = 0;
	while (j < p->b->sub_count && c < max)
	{
		if (aabb_overlap_local(p->a->sub_shapes[ia].local_aabb,
				p->b->sub_shapes[j].local_aabb))
		{
			out[c].sa = &p->a->sub_shapes[ia];
			out[c].sb = &p->b->sub_shapes[j];
			out[c].ba = p->a;
			out[c].bb = p->b;
			c++;
		}
		j++;
	}
	return (c);
}

/**
 * @brief Iterates over bricks of Body A and dispatches to single_brick check.
 */
int	test_brick_pair(t_body_pair *pair, t_shape_pair *out, int count, int max)
{
	size_t	i;

	i = 0;
	while (i < pair->a->sub_count && count < max)
	{
		count = check_single_brick(pair, i, out, count, max);
		i++;
	}
	return (count);
}

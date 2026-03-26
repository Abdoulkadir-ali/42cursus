/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midphase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static bool	aabb_overlap_local(t_aabb a, t_aabb b)
{
	if (a.max.x < b.min.x || a.min.x > b.max.x)
		return (false);
	if (a.max.y < b.min.y || a.min.y > b.max.y)
		return (false);
	if (a.max.z < b.min.z || a.min.z > b.max.z)
		return (false);
	return (true);
}

static int	test_brick_pair(t_body_pair *pair, t_shape_pair *out, int count, int max)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < pair->a->sub_count && count < max)
	{
		j = 0;
		while (j < pair->b->sub_count && count < max)
		{
			if (aabb_overlap_local(pair->a->sub_shapes[i].local_aabb,
					pair->b->sub_shapes[j].local_aabb))
			{
				out[count].sa = &pair->a->sub_shapes[i];
				out[count].sb = &pair->b->sub_shapes[j];
				out[count].ba = pair->a;
				out[count].bb = pair->b;
				count++;
			}
			j++;
		}
		i++;
	}
	return (count);
}

/**
 * @brief Brick-level AABB midphase filter.
 * For each body pair from broadphase, test all sub-shape AABB combinations.
 * Returns count of shape pairs ready for GJK narrowphase.
 */
int	midphase(t_body_pair *pairs, int n, t_shape_pair *out, int max)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (i < n && count < max)
	{
		count = test_brick_pair(&pairs[i], out, count, max);
		i++;
	}
	return (count);
}

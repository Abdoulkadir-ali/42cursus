/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

int	query_pyramid(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_pyramid	*py = &s->pyramids[idx];
	t_aabb		pyaabb;
	t_gjk_shape	sa;
	t_gjk_shape	sb;
	int			p;

	if (py->phys.is_static) return (count);
	pyaabb = pyramid_aabb(py);
	sa = (t_gjk_shape){py, gjk_support_pyramid, py->phys.center};
	p = -1;
	while (++p < s->plane_count && count < max)
		count += pyramid_vs_plane(py, &s->planes[p], &c[count], max - count);
	p = idx;
	while (++p < s->pyramid_count && count < max)
		if (aabb_overlap(pyaabb, pyramid_aabb(&s->pyramids[p])))
		{
			sb = (t_gjk_shape){&s->pyramids[p], gjk_support_pyramid, s->pyramids[p].phys.center};
			count += gjk_make_contact(&sa, &sb, &py->phys, &s->pyramids[p].phys, &py->transform, &s->pyramids[p].transform, &c[count]);
		}
	return (count);
}

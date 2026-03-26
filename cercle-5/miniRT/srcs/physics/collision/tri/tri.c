/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 10:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* *****************:********************************************************* */

#include "physics.h"
#include "scene.h"
#include "objects.h"

int	query_tri(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_tri_shape	*tr = &s->tris[idx];
	t_aabb		ta;
	int			p;

	if (tr->phys.is_static) return (count);
	ta = tri_shape_aabb(tr);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += tri_vs_plane(tr, &s->planes[p], &c[count], max - count);
		p++;
	}
	return (tri_vs_others(s, idx, tr, ta, c, count, max));
}

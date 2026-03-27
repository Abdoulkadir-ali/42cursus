/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_rect(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_rect	*rc;
	t_aabb	ra;
	int		p;

	rc = &s->rects[idx];
	if (rc->phys.is_static)
		return (count);
	ra = rect_aabb(rc);
	p = 0;
	while (p < s->plane_count && count < max)
	{
		count += rect_vs_plane(rc, &s->planes[p], &c[count], max - count);
		p++;
	}
	return (rect_vs_others(s, idx, rc, ra, c, count, max));
}

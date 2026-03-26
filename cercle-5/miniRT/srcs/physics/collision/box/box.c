/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 09:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:08:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

int	query_box(t_scene *s, int idx, t_contact *c, int count, int max)
{
	t_box *bx = &s->boxes[idx]; t_aabb ba; int p = 0;
	if (bx->phys.is_static) return (count);
	ba = box_aabb(bx);
	while (p < s->plane_count && count < max)
	{
		count += box_vs_plane(bx, &s->planes[p], &c[count], max - count);
		p++;
	}
	return (box_vs_others(s, idx, bx, ba, c, count, max));
}

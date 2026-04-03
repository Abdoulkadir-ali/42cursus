/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Tests collision between a shape and all triangles in the scene.
 */
void	loop_tris(t_contact_query *qu, t_gjk_shape *sa,
		t_physics_body *ba, t_transform *ta)
{
	size_t		p;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_tri_shape	*tr;

	p = 0;
	while (p < qu->engine->scene->tri_count && qu->count < qu->max)
	{
		tr = &qu->engine->scene->tris[p++];
		if (ba == &tr->phys)
			continue ;
		sb = (t_gjk_shape){tr, gjk_support_tri, tr->phys.pos};
		pair = (t_col_pair){sa, &sb, ba, &tr->phys, ta, &tr->xform};
		if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
			qu->count++;
	}
}

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
 * @brief Tests collision between a shape and all rects in the scene.
 */
void	loop_rects(t_contact_query *qu, t_gjk_shape *sa,
		t_physics_body *ba, t_transform *ta)
{
	size_t		p;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_rect		*r;

	p = 0;
	while (p < qu->engine->scene->rect_count && qu->count < qu->max)
	{
		r = &qu->engine->scene->rects[p++];
		if (ba == &r->phys)
			continue ;
		sb = init_gjk_shape(r, gjk_support_rect, r->phys.pos);
		pair = (t_col_pair){sa, &sb, ba, &r->phys, ta, &r->transform};
		if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
			qu->count++;
	}
}

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
 * @brief Tests collision between a shape and all pyramids in the scene.
 */
void	loop_pyramids(t_contact_query *qu, t_gjk_shape *sa,
		t_physics_body *ba, t_transform *ta)
{
	size_t		p;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_pyramid	*py;

	p = 0;
	while (p < qu->engine->scene->pyramid_count && qu->count < qu->max)
	{
		py = &qu->engine->scene->pyramids[p++];
		if (ba == &py->phys)
			continue ;
		sb = (t_gjk_shape){py, gjk_support_pyramid, py->phys.pos};
		pair = (t_col_pair){sa, &sb, ba, &py->phys, ta, &py->transform};
		if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
			qu->count++;
	}
}

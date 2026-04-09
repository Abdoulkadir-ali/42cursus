/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 10:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Tests collision between a shape and all capsules in the scene.
 */
void	loop_capsules(t_contact_query *qu, t_gjk_shape *sa,
		t_physics_body *ba, t_transform *ta)
{
	size_t		p;
	t_gjk_shape	sb;
	t_col_pair	pair;
	t_capsule	*other;

	p = 0;
	while (p < qu->engine->scene->capsule_count && qu->count < qu->max)
	{
		other = &qu->engine->scene->capsules[p++];
		if (ba == &other->phys)
			continue ;
		sb = init_gjk_shape(other, gjk_support_capsule, other->phys.center);
		pair = (t_col_pair){sa, &sb, ba, &other->phys, ta, &other->transform};
		if (gjk_make_contact(&pair, &qu->contacts[qu->count]))
			qu->count++;
	}
}

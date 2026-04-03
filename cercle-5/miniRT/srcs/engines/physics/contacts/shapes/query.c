/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 12:45:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Performs a full check of a single shape vs all objects.
 */
size_t	query_shapes(t_contact_query *qu, t_gjk_shape *sa, t_physics_body *ba,
		t_transform *ta)
{
	loop_boxes(qu, sa, ba, ta);
	loop_capsules(qu, sa, ba, ta);
	loop_cylinders(qu, sa, ba, ta);
	loop_rects(qu, sa, ba, ta);
	loop_tris(qu, sa, ba, ta);
	loop_pyramids(qu, sa, ba, ta);
	return (qu->count);
}

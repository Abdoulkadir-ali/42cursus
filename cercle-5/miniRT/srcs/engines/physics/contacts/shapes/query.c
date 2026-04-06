/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   query.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 11:06:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Performs a full check of a single shape vs all objects.
 */
size_t	query_shapes(t_contct_query *qu, t_gjk_shape *sa, t_physics_body *pb,
		t_transform *t)
{
	loop_boxes(qu, sa, pb, t);
	loop_capsules(qu, sa, pb, t);
	loop_cylinders(qu, sa, pb, t);
	loop_rects(qu, sa, pb, t);
	loop_tris(qu, sa, pb, t);
	loop_pyramids(qu, sa, pb, t);
	return (qu->count);
}

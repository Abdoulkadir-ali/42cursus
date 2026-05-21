/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 15:57:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:13:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_aabb	box_bounds(const t_box *b)
{
	t_aabb	out;
	t_vec3	e;

	e.x = fabsf(b->u.x) * b->he.x + fabsf(b->v.x) * b->he.y + fabsf(b->w.x)
		* b->he.z;
	e.y = fabsf(b->u.y) * b->he.x + fabsf(b->v.y) * b->he.y + fabsf(b->w.y)
		* b->he.z;
	e.z = fabsf(b->u.z) * b->he.x + fabsf(b->v.z) * b->he.y + fabsf(b->w.z)
		* b->he.z;
	out.min = v3_sub(b->center, e);
	out.max = v3_add(b->center, e);
	return (out);
}

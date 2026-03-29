/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_aabb	get_tri_aabb_soa(t_tri_array *t, int i)
{
	t_aabb	aabb;

	if (i < 0 || (size_t)i >= t->count)
		return (aabb_create_empty());
	aabb = aabb_create_empty();
	aabb_expand_point(&aabb, vec3(t->vx[0][i], t->vy[0][i], t->vz[0][i]));
	aabb_expand_point(&aabb, vec3(t->vx[1][i], t->vy[1][i], t->vz[1][i]));
	aabb_expand_point(&aabb, vec3(t->vx[2][i], t->vy[2][i], t->vz[2][i]));
	return (aabb);
}

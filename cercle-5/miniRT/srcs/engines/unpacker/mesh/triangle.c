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

t_tri_view	unpack_tri(const t_tri_array *t, int i)
{
	t_tri_view	tri;

	ft_memset(&tri, 0, sizeof(tri));
	if (i < 0 || (size_t)i >= t->count)
		return (tri);
	tri.v0 = vec3(t->vx[0][i], t->vy[0][i], t->vz[0][i]);
	tri.v1 = vec3(t->vx[1][i], t->vy[1][i], t->vz[1][i]);
	tri.v2 = vec3(t->vx[2][i], t->vy[2][i], t->vz[2][i]);
	tri.n = vec3(t->nx[i], t->ny[i], t->nz[i]);
	tri.mat_idx = t->mat_ids[i];
	return (tri);
}

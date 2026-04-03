/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:46:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Returns the furthest vertex of a mesh along the search direction.
 */
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir)
{
	const t_mesh	*m;
	t_vec3			best;
	double			best_d;
	double			d;
	size_t			i;

	m = (const t_mesh *)data;
	if (!m->vertices || m->vertex_count == 0)
		return (vec3(0, 0, 0));
	best = m->vertices[0].pos;
	best_d = vec3_dot(m->vertices[0].pos, dir);
	i = 1;
	while (i < m->vertex_count)
	{
		d = vec3_dot(m->vertices[i].pos, dir);
		if (d > best_d)
		{
			best_d = d;
			best = m->vertices[i].pos;
		}
		i++;
	}
	return (best);
}

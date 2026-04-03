/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_finish.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

bool	intersect_finish_hit(t_trace *trace, t_mesh *mesh, t_hit *hit,
		const t_ray *ray)
{
	t_mesh_hit	m_hit;

	if (trace->best_tri == (size_t)-1)
		return (false);
	m_hit.hit = hit;
	m_hit.mesh = mesh;
	m_hit.ray = ray;
	m_hit.bary = trace->best_uv;
	m_hit.t = trace->best_t;
	m_hit.tri = trace->best_tri;
	update_mesh_hit(&m_hit);
	return (true);
}

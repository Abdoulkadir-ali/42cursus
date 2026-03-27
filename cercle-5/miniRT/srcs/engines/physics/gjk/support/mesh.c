/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 20:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief DOD-aware GJK support point for a complex mesh.
 * Accesses vertex data from the scene's mesh pool using the shape index.
 */
t_vec3	gjk_support_mesh(const t_gjk_shape *s, t_vec3 dir)
{
	const t_mesh	*m;

	if (s->scene == NULL || s->scene->meshes == NULL)
		return (vec3(0, 0, 0));
	m = &s->scene->meshes[s->idx];
	if (!m->vertices || m->vertex_count == 0)
		return (vec3(0, 0, 0));
	return (gjk_support_list(m->vertices, m->vertex_count, dir));
}

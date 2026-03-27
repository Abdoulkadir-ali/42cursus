/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:27:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief GJK support point for a complex mesh. Iterates through all vertices.
 */
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir)
{
	const t_mesh	*m;

	m = (const t_mesh *)data;
	if (!m->vertices || m->vertex_count == 0)
		return (vec3(0, 0, 0));
	return (gjk_support_list(m->vertices, m->vertex_count, dir));
}

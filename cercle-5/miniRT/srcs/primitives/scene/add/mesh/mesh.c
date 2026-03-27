/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 21:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	scene_add_mesh(t_scene *scene, t_mesh mesh)
{
	t_mat4		m;
	t_tri_shape	tri;
	int			i;

	if (vec3_mag_sq(mesh.transform.scale) < SCALE_EPSILON)
		mesh.transform.scale = vec3(1, 1, 1);
	m = mat4_transform(mesh.transform);
	ft_memset(&tri, 0, sizeof(t_tri_shape));
	tri.mat_id = mesh.mat_id;
	i = 0;
	while (i < mesh.tri_count)
	{
		if (!DYNARRAY_ENSURE_INT((void **)&scene->triangles, &scene->tri_count,
				&scene->tri_cap, sizeof(t_tri_shape)))
			return (false);
		tri.v[0] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 0]]);
		tri.v[1] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 1]]);
		tri.v[2] = mat4_mul_pos(m, mesh.vertices[mesh.indices[i * 3 + 2]]);
		scene->triangles[scene->tri_count++] = tri;
		i++;
	}
	mesh_free(&mesh);
	return (true);
}

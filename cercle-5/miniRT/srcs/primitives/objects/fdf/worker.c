/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "raytracing.h"
#include "debug.h"

/**
 * Main parser for FDF files. Converts heightmap to mesh.
 */

bool	parse_fdf_worker(const char *path, t_scene *scene)
{
	t_mesh		mesh;
	t_vec2		dims;
	size_t		v_count;
	size_t		i_count;
	t_fdf_mode	mode;

	ft_print_debug("FDF: Starting parse for '%s'\n", path);
	if (!fdf_get_dimensions(path, &dims))
	{
		ft_print_debug("FDF: ERROR: Failed to get dimensions for %s\n", path);
		return (false);
	}
	ft_print_debug("FDF: %s dimensions: %g x %g\n", path, dims.x, dims.y);
	v_count = (size_t)dims.x * (size_t)dims.y;
	i_count = ((size_t)dims.x - 1) * ((size_t)dims.y - 1) * 2 * 3;
	if (!fdf_init_mesh(&mesh, v_count, i_count, path))
	{
		ft_print_debug("FDF: ERROR: Failed to init mesh for %s\n", path);
		return (false);
	}
	ft_print_debug("FDF: Mesh initialized: v=%zu, tri=%zu\n",
		v_count, mesh.tri_count);
	mesh.extra = ft_calloc(v_count, sizeof(unsigned int));
	mode = fdf_detect_mode(path);
	ft_print_debug("FDF: mode=%s\n",
		mode == FDF_MODE_PICTURE ? "PICTURE" : "HEIGHT_GRADIENT");
	fdf_fill_data(path, &mesh, dims);
	ft_print_debug("FDF: Fill done. v[0]=(%g,%g,%g) v[1]=(%g,%g,%g)\n",
		mesh.vertices[0].pos.x, mesh.vertices[0].pos.y,
		mesh.vertices[0].pos.z,
		mesh.vertices[1].pos.x, mesh.vertices[1].pos.y,
		mesh.vertices[1].pos.z);
	fdf_compute_normals(scene->pool, &mesh, dims);
	fdf_triangulate(scene->pool, &mesh, dims);
	ft_print_debug("FDF: Triangulation done. idx[0..5]=%zu %zu %zu | %zu %zu %zu\n",
		mesh.indices[0], mesh.indices[1], mesh.indices[2],
		mesh.indices[3], mesh.indices[4], mesh.indices[5]);
	mesh_build_bvh(&mesh);
	ft_print_debug("FDF: BVH built. bvh_nodes=%zu BBox Min=(%g,%g,%g), Max=(%g,%g,%g)\n",
		mesh.bvh_node_count,
		mesh.bbox.min.x, mesh.bbox.min.y, mesh.bbox.min.z,
		mesh.bbox.max.x, mesh.bbox.max.y, mesh.bbox.max.z);
	mesh.mat_id = scene_add_material(scene, vec3(200, 200, 200)).i;
	fdf_apply_mode(&mesh, scene, dims, mode);
	ft_print_debug("FDF: Material assigned: mat_id=%zu\n", mesh.mat_id);
	if (!scene_add_mesh(scene, mesh))
	{
		ft_print_debug("FDF: ERROR: Failed to add mesh to scene.\n");
		mesh_free(&mesh);
		return (false);
	}
	ft_print_debug("FDF: Successfully added mesh '%s'\n", path);
	return (true);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 00:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "raytracing.h"
#include "debug.h"

static bool	fdf_setup_state(t_mesh *mesh, t_vec2s dims,
		t_fdf_state **out_state)
{
	t_fdf_state	*state;
	size_t		v_count;

	v_count = dims.x * dims.y;
	state = ft_calloc(1, sizeof(t_fdf_state));
	if (!state)
		return (false);
	state->dims = dims;
	state->colors = ft_calloc(v_count, sizeof(unsigned int));
	if (!state->colors)
	{
		free(state);
		return (false);
	}
	mesh->extra = state->colors;
	*out_state = state;
	return (true);
}

static void	fdf_finalize_parsing(t_mesh *mesh, t_scene *scene)
{
	t_fdf_state	*state;

	state = (t_fdf_state *)mesh->extra;
	fdf_compute_normals(scene->pool, mesh, state->dims);
	fdf_triangulate(scene->pool, mesh, state->dims);
	mesh_build_bvh(mesh);
	mesh->mat_id = scene_add_material(scene, vec3(200, 200, 200)).i;
	fdf_apply_mode(mesh, scene, state);
}

static const char	*fdf_get_mode_str(t_fdf_mode mode)
{
	if (mode == FDF_MODE_PICTURE)
		return ("PICTURE");
	return ("HEIGHT_GRADIENT");
}

bool	parse_fdf_worker(const char *path, t_scene *scene)
{
	t_mesh			mesh;
	t_vec2s			dims;
	t_fdf_mode		mode;
	t_fdf_state		*state;

	if (!fdf_get_dimensions(path, &dims))
		return (false);
	if (!fdf_init_mesh(&mesh, dims.x * dims.y, (dims.x - 1) * (dims.y - 1)
			* 2 * 3, path))
		return (false);
	if (!fdf_setup_state(&mesh, dims, &state))
		return (false);
	mode = fdf_detect_mode(path);
	ft_print_debug("FDF: mode=%s\n", fdf_get_mode_str(mode));
	fdf_fill_data(path, &mesh, dims);
	mesh.extra = state;
	state->mode = mode;
	mesh.is_fdf = true;
	fdf_finalize_parsing(&mesh, scene);
	if (!scene_add_mesh(scene, mesh))
		return (mesh_free(&mesh), false);
	scene_add_group_for_subs(scene, path, scene->mesh_count - 1);
	return (true);
}

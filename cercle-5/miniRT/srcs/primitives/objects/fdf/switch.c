/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 18:19:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "raytracing.h"
#include "scene.h"

void	fdf_switch_mode(t_mesh *mesh, t_scene *scene, t_fdf_mode new_mode)
{
	t_fdf_state	*state;

	if (!mesh || !mesh->is_fdf || !mesh->extra)
		return ;
	state = (t_fdf_state *)mesh->extra;
	if (state->mode == new_mode)
		return ;
	mesh->extra = state->colors;
	fdf_fill_data(mesh->name, mesh, state->dims);
	mesh->extra = state;
	fdf_compute_normals(scene->pool, mesh, state->dims);
	fdf_apply_mode(mesh, scene, state->dims, new_mode, state->colors);
	state->mode = new_mode;
	mesh->bvh_dirty = true;
	mesh_build_bvh(mesh);
}

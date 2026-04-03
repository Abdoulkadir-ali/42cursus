#include "primitives.h"
/* ************************************************************************** */
/*                                                                            */
void	refresh_editor_snaps(t_scene *scene, size_t start_idx);
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:02:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:46:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	calculate_mesh_bounds(t_scene *scene, size_t start_idx,
				t_vec3 *min_pt, t_vec3 *max_pt)
{
	size_t	i;

	*min_pt = vec3(INFINITY, INFINITY, INFINITY);
	*max_pt = vec3(-INFINITY, -INFINITY, -INFINITY);
	i = start_idx;
	while (i < scene->mesh_count)
	{
		*min_pt = vec3_min(*min_pt, scene->meshes[i].bbox.min);
		*max_pt = vec3_max(*max_pt, scene->meshes[i].bbox.max);
		i++;
	}
}

static void	set_camera_frame(t_scene *scene, t_vec3 center, double size)
{
	t_vec3	fwd;

	scene->camera.transform.pos = vec3_add(center, vec3(0, size * 0.3, size
				* 1.2));
	fwd = vec3_norm(vec3_sub(center, scene->camera.transform.pos));
	scene->camera.transform.forward = fwd;
	scene->camera.transform.rotation.pitch = asin(fwd.y);
	scene->camera.transform.rotation.yaw = atan2(fwd.x, fwd.z);
	if (scene->light_count > 0)
		scene->lights[0].transform.pos = vec3_add(center, vec3(size * 0.5, size
					* 1.0, size * 0.8));
}

static void	apply_voffset(t_scene *scene, size_t start_idx, double voff)
{
	size_t	i;

	i = start_idx;
	while (i < scene->mesh_count)
	{
		scene->meshes[i].transform.pos.y += voff;
		if (scene->meshes[i].transform.scale.x == 0.0)
			scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&scene->meshes[i], scene->meshes[i].transform);
		i++;
	}
}

void	align_and_frame_meshes(t_scene *scene, size_t start_idx)
{
	t_vec3	pts[3];
	double	sz_off[2];

	calculate_mesh_bounds(scene, start_idx, &pts[0], &pts[1]);
	sz_off[1] = 0.0;
	if (pts[0].y < 0)
		sz_off[1] = -pts[0].y;
	apply_voffset(scene, start_idx, sz_off[1]);
	refresh_editor_snaps(scene, start_idx);
	pts[2] = vec3_add(vec3_scale(vec3_add(pts[0], pts[1]), 0.5),
			vec3(0, sz_off[1], 0));
	sz_off[0] = vec3_mag(vec3_sub(pts[1], pts[0]));
	if (sz_off[0] < 1e-6)
		sz_off[0] = 10.0;
	set_camera_frame(scene, pts[2], sz_off[0]);
}

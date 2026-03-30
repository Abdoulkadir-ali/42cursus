/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:02:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 16:02:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"

static void	refresh_mesh_snaps(t_scene *scene, int start_idx)
{
	t_mesh	*m;
	int		i;

	i = start_idx - 1;
	while (++i < scene->mesh_count)
	{
		m = &scene->meshes[i];
		if (m->edit_snap_verts)
			ft_memcpy(m->edit_snap_verts, m->vertices,
				sizeof(t_vec3) * m->vertex_count);
		if (m->normals && m->edit_snap_norms)
			ft_memcpy(m->edit_snap_norms, m->normals,
				sizeof(t_vec3) * m->vertex_count);
		m->edit_snap_pivot = vec3(
				(m->bbox.min.x + m->bbox.max.x) * 0.5,
				(m->bbox.min.y + m->bbox.max.y) * 0.5,
				(m->bbox.min.z + m->bbox.max.z) * 0.5);
	}
}

void	refresh_editor_snaps(t_scene *scene, int start_idx)
{
	t_mesh_group	*g;
	t_aabb			bbox;
	int				i;
	int				gi;

	refresh_mesh_snaps(scene, start_idx);
	gi = -1;
	while (++gi < scene->group_count)
	{
		g = &scene->groups[gi];
		if (g->start < start_idx)
			continue ;
		bbox = scene->meshes[g->start].bbox;
		i = g->start;
		while (++i < g->start + g->sub_count && i < scene->mesh_count)
			bbox = aabb_union(&bbox, &scene->meshes[i].bbox);
		g->pivot = vec3(
				(bbox.min.x + bbox.max.x) * 0.5,
				(bbox.min.y + bbox.max.y) * 0.5,
				(bbox.min.z + bbox.max.z) * 0.5);
	}
}

static void	calculate_mesh_bounds(t_scene *scene, int start_idx,
				t_vec3 *min_pt, t_vec3 *max_pt)
{
	int	i;

	*min_pt = vec3(INFINITY, INFINITY, INFINITY);
	*max_pt = vec3(-INFINITY, -INFINITY, -INFINITY);
	i = start_idx - 1;
	while (++i < scene->mesh_count)
	{
		*min_pt = vec3_min(*min_pt, scene->meshes[i].bbox.min);
		*max_pt = vec3_max(*max_pt, scene->meshes[i].bbox.max);
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

void	align_and_frame_meshes(t_scene *scene, int start_idx)
{
	t_vec3	pts[3];
	double	sz_off[2];
	int		i;

	calculate_mesh_bounds(scene, start_idx, &pts[0], &pts[1]);
	sz_off[1] = 0.0;
	if (pts[0].y < 0)
		sz_off[1] = -pts[0].y;
	i = start_idx - 1;
	while (++i < scene->mesh_count)
	{
		scene->meshes[i].transform.pos.y += sz_off[1];
		if (scene->meshes[i].transform.scale.x == 0.0)
			scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&scene->meshes[i], scene->meshes[i].transform);
	}
	refresh_editor_snaps(scene, start_idx);
	pts[2] = vec3_add(vec3_scale(vec3_add(pts[0], pts[1]), 0.5),
			vec3(0, sz_off[1], 0));
	sz_off[0] = vec3_mag(vec3_sub(pts[1], pts[0]));
	if (sz_off[0] < 1e-6)
		sz_off[0] = 10.0;
	set_camera_frame(scene, pts[2], sz_off[0]);
}

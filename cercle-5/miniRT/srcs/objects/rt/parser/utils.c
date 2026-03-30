/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "scene.h"
#include <unistd.h>

static bool	is_mesh_ext(const char *ext)
{
	return (ft_strcmp(ext, "fbx") == 0 || ft_strcmp(ext, "obj") == 0
		|| ft_strcmp(ext, "fdf") == 0 || ft_strcmp(ext, "glb") == 0);
}

/*
** After handle_mesh_injection bakes the identity transform (pos=0,rot=0,scale=1)
** a second bake is applied here to lift the model above the ground plane and
** auto-frame the camera.  We must refresh two editor-side snapshots that the
** first (identity) bake set to the pre-lift positions:
**   1. mesh->edit_snap_verts/norms/pivot  — used by transform_panel live-drag
**   2. group pivot in scene->groups[]     — used by inspector / gizmo display
*/
static void	refresh_editor_snaps(t_scene *scene, int start_idx)
{
	t_mesh			*m;
	t_mesh_group	*g;
	t_aabb			bbox;
	int				i;
	int				gi;

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
	/* Re-compute the group pivot from the now-lifted submesh bboxes */
	gi = 0;
	while (gi < scene->group_count)
	{
		g = &scene->groups[gi];
		if (g->start < start_idx)
		{
			gi++;
			continue ;
		}
		bbox = scene->meshes[g->start].bbox;
		i = g->start + 1;
		while (i < g->start + g->sub_count && i < scene->mesh_count)
			bbox = aabb_union(&bbox, &scene->meshes[i++].bbox);
		g->pivot = vec3(
			(bbox.min.x + bbox.max.x) * 0.5,
			(bbox.min.y + bbox.max.y) * 0.5,
			(bbox.min.z + bbox.max.z) * 0.5);
		gi++;
	}
}

/*
** Lifts the model above the ground plane (Y-bake) and auto-frames the camera.
** Called only for direct mesh loads — .rt scenes handle positioning explicitly.
** After the second bake, editor snapshots and group pivots are refreshed.
*/
static void	align_and_frame_meshes(t_scene *scene, int start_idx)
{
	t_vec3	min_pt;
	t_vec3	max_pt;
	t_vec3	center;
	t_vec3	fwd;
	double	size;
	int		i;
	double	offset_y;

	if (start_idx >= scene->mesh_count)
		return ;
	min_pt = vec3(INFINITY, INFINITY, INFINITY);
	max_pt = vec3(-INFINITY, -INFINITY, -INFINITY);
	i = start_idx - 1;
	while (++i < scene->mesh_count)
	{
		min_pt = vec3_min(min_pt, scene->meshes[i].bbox.min);
		max_pt = vec3_max(max_pt, scene->meshes[i].bbox.max);
	}
	offset_y = 0.0;
	if (min_pt.y < 0)
		offset_y = -min_pt.y;
	/* Bake the Y lift into vertices so the BVH sees the final positions. */
	i = start_idx - 1;
	while (++i < scene->mesh_count)
	{
		scene->meshes[i].transform.pos.y += offset_y;
		if (scene->meshes[i].transform.scale.x == 0.0)
			scene->meshes[i].transform.scale = vec3(1, 1, 1);
		mesh_apply_transform(&scene->meshes[i], scene->meshes[i].transform);
	}
	refresh_editor_snaps(scene, start_idx);
	center = vec3_scale(vec3_add(min_pt, max_pt), 0.5);
	center.y += offset_y;
	size = vec3_mag(vec3_sub(max_pt, min_pt));
	if (size < 1e-6)
		size = 10.0;
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

/*
** Builds a minimal RT scene string for a direct mesh load and feeds it through
** the canonical RT parser via a pipe, so that handle_mesh_injection runs for
** full cache + material-clone + group registration.
** The mesh line uses identity transform (pos=0,rot=0,scale=1); the Y-lift bake
** is applied afterwards by align_and_frame_meshes.
*/
static bool	parse_as_default_rt(const char *ext, const char *path,
				t_scene *scene)
{
	char	buf[2048];
	int		fds[2];
	int		n;
	bool	ok;

	n = snprintf(buf, sizeof(buf),
		"A 0.3 255,255,255\n"
		"C 0,0,1 0,0,-1 70\n"
		"L -30,200,30 0.8 255,255,255\n"
		"L -15,40,10 0.8 100,50,30\n"
		"L 0,60,-20 0.8 100,50,30\n"
		"pl 0,0,0 0,1,0 150,150,150\n"
		"%s %s 0,0,0 0,0,0 1.0\n",
		ext, path);
	if (n <= 0 || (size_t)n >= sizeof(buf))
	{
		fprintf(stderr, "Error: default RT string too long for %s\n", path);
		return (false);
	}
	if (pipe(fds) != 0)
	{
		perror("pipe");
		return (false);
	}
	if (write(fds[1], buf, (size_t)n) < 0)
	{
		close(fds[1]);
		close(fds[0]);
		return (false);
	}
	close(fds[1]);
	ok = parse_rt_fd(fds[0], scene);
	close(fds[0]);
	return (ok);
}

static bool	parse_by_ext(const char *ext, const char *path, t_scene *scene)
{
	int	start_idx;
	bool	ok;

	if (ft_strcmp(ext, "rt") == 0)
		return (parse_rt(path, scene));
	if (!is_mesh_ext(ext))
	{
		printf("Error: Unsupported file extension: .%s\n", ext);
		return (false);
	}
	start_idx = scene->mesh_count;
	ok = parse_as_default_rt(ext, path, scene);
	if (ok)
		align_and_frame_meshes(scene, start_idx);
	return (ok);
}

static t_scene	*init_scene(const char *path, void *mlx)
{
	t_scene	*scene;

	scene = create_scene(path);
	if (!scene)
	{
		printf("Error: Failed to create scene object for %s\n", path);
		return (NULL);
	}
	scene->mlx = mlx;
	return (scene);
}

t_scene	*parse_file(const char *path, void *mlx)
{
	t_scene		*scene;
	const char	*ext;
	bool		success;

	printf("PARSING_FILE: %s\n", path);
	fflush(stdout);
	ext = rt_get_extension(path);
	if (!validate_file(path))
	{
		printf("Error: File not found or invalid: %s\n", path);
		return (NULL);
	}
	scene = init_scene(path, mlx);
	if (!scene)
		return (NULL);
	success = parse_by_ext(ext, path, scene);
	if (!success)
	{
		printf("Error: Failed to parse %s\n", path);
		destroy_scene(scene);
		return (NULL);
	}
	return (scene);
}

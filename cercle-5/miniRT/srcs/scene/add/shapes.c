/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:35:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/*
** Adds a sphere to the scene.
*/
bool	scene_add_sphere(t_scene *scene, t_sphere sphere)
{
	int	mat_id;

	mat_id = scene_add_material(scene, sphere.temp_color);
	if (mat_id < 0)
		return (false);
	sphere.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->spheres, &scene->sphere_count,
			&scene->sphere_cap, sizeof(t_sphere)))
		return (false);
	if (vec3_mag_sq(sphere.transform.scale) < 1e-6)
		sphere.transform.scale = vec3(1, 1, 1);
	scene->spheres[scene->sphere_count++] = sphere;
	return (true);
}

/*
** Adds a plane to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_plane(t_scene *scene, t_plane plane)
{
	int	mat_id;

	mat_id = scene_add_material(scene, plane.temp_color);
	if (mat_id < 0)
		return (false);
	plane.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->planes, &scene->plane_count,
			&scene->plane_cap, sizeof(t_plane)))
		return (false);
	if (vec3_mag_sq(plane.transform.scale) < 1e-6)
		plane.transform.scale = vec3(1, 1, 1);
	scene->planes[scene->plane_count++] = plane;
	return (true);
}

/*
** Adds a cylinder to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cylinder(t_scene *scene, t_cylinder cylinder)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cylinder.temp_color);
	if (mat_id < 0)
		return (false);
	cylinder.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->cylinders, &scene->cylinder_count,
			&scene->cylinder_cap, sizeof(t_cylinder)))
		return (false);
	if (vec3_mag_sq(cylinder.transform.scale) < 1e-6)
		cylinder.transform.scale = vec3(1, 1, 1);
	scene->cylinders[scene->cylinder_count++] = cylinder;
	return (true);
}

/*
** Adds a cone to the scene.
** Automatically creates/retrieves the material based on temp_color.
*/
bool	scene_add_cone(t_scene *scene, t_cone cone)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cone.temp_color);
	if (mat_id < 0)
		return (false);
	cone.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->cones, &scene->cone_count,
			&scene->cone_cap, sizeof(t_cone)))
		return (false);
	if (vec3_mag_sq(cone.transform.scale) < 1e-6)
		cone.transform.scale = vec3(1, 1, 1);
	scene->cones[scene->cone_count++] = cone;
	return (true);
}

bool	scene_add_tri(t_scene *scene, t_tri_shape tri)
{
	int	mat_id;

	mat_id = scene_add_material(scene, tri.temp_color);
	if (mat_id < 0)
		return (false);
	tri.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->tris, &scene->tri_count,
			&scene->tri_cap, sizeof(t_tri_shape)))
		return (false);
	scene->tris[scene->tri_count++] = tri;
	return (true);
}

bool	scene_add_rect(t_scene *scene, t_rect rect)
{
	int	mat_id;

	mat_id = scene_add_material(scene, rect.temp_color);
	if (mat_id < 0)
		return (false);
	rect.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->rects, &scene->rect_count,
			&scene->rect_cap, sizeof(t_rect)))
		return (false);
	scene->rects[scene->rect_count++] = rect;
	return (true);
}

bool	scene_add_pyramid(t_scene *scene, t_pyramid py)
{
	int	mat_id;

	mat_id = scene_add_material(scene, py.temp_color);
	if (mat_id < 0)
		return (false);
	py.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->pyramids, &scene->pyramid_count,
			&scene->pyramid_cap, sizeof(t_pyramid)))
		return (false);
	scene->pyramids[scene->pyramid_count++] = py;
	return (true);
}

bool	scene_add_box(t_scene *scene, t_box box)
{
	int	mat_id;

	mat_id = scene_add_material(scene, box.temp_color);
	if (mat_id < 0)
		return (false);
	box.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->boxes, &scene->box_count,
			&scene->box_cap, sizeof(t_box)))
		return (false);
	scene->boxes[scene->box_count++] = box;
	return (true);
}

bool	scene_add_capsule(t_scene *scene, t_capsule cap)
{
	int	mat_id;

	mat_id = scene_add_material(scene, cap.temp_color);
	if (mat_id < 0)
		return (false);
	cap.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->capsules, &scene->capsule_count,
			&scene->capsule_cap, sizeof(t_capsule)))
		return (false);
	scene->capsules[scene->capsule_count++] = cap;
	return (true);
}

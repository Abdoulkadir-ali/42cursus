/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 10:25:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Initializes the basic object arrays for the scene.
 * @param s Pointer to the scene.
 * @return true on success, false on allocation failure.
 */
static bool	init_basic_arrays(t_scene *s)
{
	s->sphere_cap = INIT_SPHERE_CAP;
	s->spheres = ft_calloc(s->sphere_cap, sizeof(t_sphere));
	s->plane_cap = INIT_PLANE_CAP;
	s->planes = ft_calloc(s->plane_cap, sizeof(t_plane));
	s->cylinder_cap = INIT_CYL_CAP;
	s->cylinders = ft_calloc(s->cylinder_cap, sizeof(t_cylinder));
	s->cone_cap = INIT_CYL_CAP;
	s->cones = ft_calloc(s->cone_cap, sizeof(t_cone));
	s->mesh_cap = INIT_MESH_CAP;
	s->meshes = ft_calloc(s->mesh_cap, sizeof(t_mesh));
	s->anim_cap = INIT_ANIM_CAP;
	s->animated = ft_calloc(s->anim_cap, sizeof(t_skinned_mesh));
	s->group_cap = INIT_GROUP_CAP;
	s->groups = ft_calloc(s->group_cap, sizeof(t_mesh_group));
	return (s->spheres && s->planes && s->cylinders && s->cones
		&& s->meshes && s->animated && s->groups);
}

/**
 * @brief Initializes the material and polygon arrays for the scene.
 * @param s Pointer to the scene.
 * @return true on success, false on allocation failure.
 */
static bool	init_ext_arrays(t_scene *s)
{
	s->mat_cap = INIT_MAT_CAP;
	s->materials = ft_calloc(s->mat_cap, sizeof(t_material));
	s->light_cap = INIT_LIGHT_CAP;
	s->lights = ft_calloc(s->light_cap, sizeof(t_light));
	s->tri_cap = INIT_TRI_CAP;
	s->tris = ft_calloc(s->tri_cap, sizeof(t_tri_shape));
	s->rect_cap = INIT_RECT_CAP;
	s->rects = ft_calloc(s->rect_cap, sizeof(t_rect));
	s->pyramid_cap = INIT_PYRAMID_CAP;
	s->pyramids = ft_calloc(s->pyramid_cap, sizeof(t_pyramid));
	s->box_cap = INIT_BOX_CAP;
	s->boxes = ft_calloc(s->box_cap, sizeof(t_box));
	s->capsule_cap = INIT_CAPSULE_CAP;
	s->capsules = ft_calloc(s->capsule_cap, sizeof(t_capsule));
	return (s->materials && s->lights && s->tris && s->rects
		&& s->pyramids && s->boxes && s->capsules);
}

/**
 * @brief Creates a new scene with default settings and empty object lists.
 * @param name The name of the scene.
 * @return t_scene* Pointer to the newly created scene, or NULL on failure.
 */
t_scene	*create_scene(const char *name)
{
	t_scene	*s;

	s = ft_calloc(1, sizeof(*s));
	if (!s)
		return (NULL);
	if (name)
		s->name = ft_strdup(name);
	if (!init_basic_arrays(s) || !init_ext_arrays(s))
	{
		destroy_scene(s);
		return (NULL);
	}
	s->ambient.brightness = 0;
	s->ambient.rgb = vec3(0, 0, 0);
	s->simulate_physics = false;
	s->version = 1;
	scene_add_material(s, vec3(200, 160, 255));
	return (s);
}

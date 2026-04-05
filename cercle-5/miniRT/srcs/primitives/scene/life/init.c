/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 15:55:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 18:24:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	init_arrays_more(t_scene *s)
{
	s->cone_cap = INIT_CYL_CAP;
	s->cones = ft_calloc(s->cone_cap, sizeof(t_cone));
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
	if (!s->cones || !s->tris || !s->rects || !s->pyramids
		|| !s->boxes || !s->capsules)
		return (false);
	return (true);
}

bool	init_scene_arrays(t_scene *s)
{
	s->sphere_cap = INIT_SPHERE_CAP;
	s->spheres = ft_calloc(s->sphere_cap, sizeof(t_sphere));
	s->plane_cap = INIT_PLANE_CAP;
	s->planes = ft_calloc(s->plane_cap, sizeof(t_plane));
	s->cylinder_cap = INIT_CYL_CAP;
	s->cylinders = ft_calloc(s->cylinder_cap, sizeof(t_cylinder));
	s->mesh_cap = INIT_MESH_CAP;
	s->meshes = ft_calloc(s->mesh_cap, sizeof(t_mesh));
	s->anim_cap = INIT_ANIM_CAP;
	s->animated = ft_calloc(s->anim_cap, sizeof(t_skinned_mesh));
	s->group_cap = INIT_GROUP_CAP;
	s->groups = ft_calloc(s->group_cap, sizeof(t_mesh_group));
	s->mat_cap = INIT_MAT_CAP;
	s->materials = ft_calloc(s->mat_cap, sizeof(t_material));
	s->light_cap = INIT_LIGHT_CAP;
	s->lights = ft_calloc(s->light_cap, sizeof(t_light));
	if (!s->spheres || !s->planes || !s->cylinders || !s->meshes || !s->animated
		|| !s->materials || !s->lights || !s->groups)
		return (false);
	return (init_arrays_more(s));
}

t_scene	*create_scene(const char *name)
{
	t_scene	*s;

	s = ft_calloc(1, sizeof(*s));
	if (!s)
		return (NULL);
	if (name)
		s->name = ft_strdup(name);
	if (!init_scene_arrays(s))
	{
		destroy_scene(s);
		return (NULL);
	}
	s->pool = ft_calloc(1, sizeof(t_thread_pool));
	if (s->pool)
		threads_init(s->pool);
	s->ambient.brightness = 0;
	s->ambient.rgb = vec3(0, 0, 0);
	pthread_rwlock_init(&s->bvh_lock, NULL);
	return (s);
}

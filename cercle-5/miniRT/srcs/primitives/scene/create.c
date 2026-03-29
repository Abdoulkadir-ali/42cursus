/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:06:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "material.h"

/**
 * @brief Initializes the basic object arrays for the scene.
 * @param s Pointer to the scene.
 * @return true on success, false on allocation failure.
 */
static bool	init_basic_arrays(t_scene *s)
{

	/* Initialize dynamic arrays used by the DOD scene layout. */
	/* Animated skinned-mesh array allocated on demand by scene_add_animated */
	s->anim_cap = 0;
	s->animated = NULL;
	s->anim_count = 0;

	/* Primitives start empty; allocator will grow them on demand. */
	s->primitives.types = NULL;
	s->primitives.px = NULL;
	s->primitives.py = NULL;
	s->primitives.pz = NULL;
	s->primitives.ax = NULL;
	s->primitives.ay = NULL;
	s->primitives.az = NULL;
	s->primitives.tx = NULL;
	s->primitives.ty = NULL;
	s->primitives.tz = NULL;
	s->primitives.radii = NULL;
	s->primitives.heights = NULL;
	s->primitives.ex = NULL;
	s->primitives.ey = NULL;
	s->primitives.ez = NULL;
	s->primitives.mat_ids = NULL;
	s->primitives.is_static = NULL;
	s->primitives.has_phys = NULL;
	s->primitives.abb_min_x = NULL;
	s->primitives.abb_min_y = NULL;
	s->primitives.abb_min_z = NULL;
	s->primitives.abb_max_x = NULL;
	s->primitives.abb_max_y = NULL;
	s->primitives.abb_max_z = NULL;
	s->primitives.phys_idx = NULL;
	s->primitives.float_slab = NULL;
	s->primitives.count = 0;
	s->primitives.capacity = 0;
	s->prim_meta = NULL;
	s->mesh_asset_meta = NULL;
	s->mesh_instance_meta = NULL;
	s->mat_meta = NULL;
	s->plane_indices = NULL;
	s->plane_count = 0;
	s->plane_cap = 0;
	return (true);
}

/**
 * @brief Initializes the material and polygon arrays for the scene.
 * @param s Pointer to the scene.
 * @return true on success, false on allocation failure.
 */
static bool	init_ext_arrays(t_scene *s)
{

	/* Materials and lights: allocate initial pools */
	s->mat_cap = INIT_MAT_CAP;
	s->materials = ft_calloc(s->mat_cap, sizeof(t_material));
	s->mat_count = 0;

	int	i;

	s->light_cap = INIT_LIGHT_CAP;
	s->lights = ft_calloc(s->light_cap, sizeof(t_light));
	s->light_count = 0;

	/* Triangle SoA is empty until meshes are added; pointers initialized NULL. */
	i = 0;
	while (i < 3)
	{
		s->tri_soa.vx[i] = NULL;
		s->tri_soa.vy[i] = NULL;
		s->tri_soa.vz[i] = NULL;
		i++;
	}
	i = 0;
	while (i < 2)
	{
		s->tri_soa.ex[i] = NULL;
		s->tri_soa.ey[i] = NULL;
		s->tri_soa.ez[i] = NULL;
		i++;
	}
	s->tri_soa.nx = NULL;
	s->tri_soa.ny = NULL;
	s->tri_soa.nz = NULL;
	s->tri_soa.tx = NULL;
	s->tri_soa.ty = NULL;
	s->tri_soa.tz = NULL;
	s->tri_soa.mat_ids = NULL;
	s->tri_soa.float_slab = NULL;
	s->tri_soa.count = 0;
	s->tri_soa.cap = 0;

	/* Animation clips */
	/* Animation clips allocated on demand */
	s->clip_cap = 0;
	s->clips = NULL;
	s->clip_count = 0;

	return (s->materials && s->lights);
}

/**
 * @brief Creates a new scene with default settings and empty object lists.
 * @note Increments scene->version must be called by callers after mutations.
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
	s->version = 1;
	scene_add_material_from_color(s, vec3(200, 160, 255));
	return (s);
}

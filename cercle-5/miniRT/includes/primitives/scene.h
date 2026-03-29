/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 08:40:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

/* --- INITIAL CAPACITIES --- */
# define INIT_SPHERE_CAP 16
# define INIT_PLANE_CAP 16
# define INIT_CYL_CAP 16
# define INIT_CONE_CAP 16
# define INIT_BOX_CAP 32
# define INIT_CAPSULE_CAP 32
# define INIT_RECT_CAP 32
# define INIT_PYRAMID_CAP 32
# define INIT_TRI_CAP 64
# define INIT_LIGHT_CAP 8
# define INIT_MAT_CAP 32
# define INIT_MESH_CAP 8
# define INIT_GROUP_CAP 32
# define INIT_ANIM_CAP 4

# include "libft.h"
# include "objects.h"
# include "anim.h"

typedef struct s_emissive_ref
{
	t_type				type;
	int					index;
	float				cull_sq;
}						t_emissive_ref;

typedef struct s_scene
{
	char							*name;

	/* 100% DOD Unified Storage (SoA) */
	t_primitive_array				primitives;
	t_tri_array						tri_soa;

	/* Dynamic & Animated Entity Arrays */
	t_mesh							*meshes;
	size_t							mesh_count;
	size_t							mesh_cap;

	t_mesh_group					*groups;
	size_t							group_count;
	size_t							group_cap;
	t_skinned_mesh					*animated;
	size_t							anim_count;
	size_t							anim_cap;

	/* Global Structure Data */
	t_material						*materials;
	size_t							mat_count;
	size_t							mat_cap;
	t_ambient						ambient;
	t_camera						camera;

	/* Unified Light Array (DOD) */
	t_light							*lights;
	size_t							light_count;
	size_t							light_cap;

	t_animation						*clips;
	size_t							clip_count;
	size_t							clip_cap;
	uint32_t						version;
	void							*mlx;

	t_emissive_ref					*emissive_cache;
	size_t							emissive_count;
	int								*plane_indices;
	size_t							plane_count;
	size_t							plane_cap;
	struct s_physics				*phys;
	/* Cold metadata — parallel to runtime, NULL = no metadata */
	t_primitive_metadata				*prim_meta;
	t_mesh_asset_metadata				**mesh_asset_meta;
	t_mesh_instance_metadata			**mesh_instance_meta;
	t_material_metadata					**mat_meta;
}	t_scene;

/* ------------------------------------------------------------------------- */
/*                             SCENE MANAGEMENT                              */
/* ------------------------------------------------------------------------- */

t_scene		*create_scene(const char *name);
void		destroy_scene(t_scene *scene);

static inline void	scene_mark_dirty(t_scene *s)
{
	if (s)
		s->version++;
}

#endif

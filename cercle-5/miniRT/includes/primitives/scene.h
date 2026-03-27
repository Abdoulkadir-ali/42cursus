/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "objects.h"

typedef struct s_animation		t_animation;
typedef struct s_skinned_mesh		t_skinned_mesh;
typedef struct s_emissive_ref		t_emissive_ref;

typedef struct s_scene
{
	char							*name;

	/* 100% DOD Unified Storage (SoA) */
	t_primitive_array				primitives;
	t_tri_array						tri_soa;

	/* Dynamic & Animated Entity Arrays */
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
	void							*physics;    /* Opaque pointer to t_physics engine */
	t_emissive_ref					*emissive_cache;
	bool							simulate_physics;
}	t_scene;

/* ------------------------------------------------------------------------- */
/*                             SCENE MANAGEMENT                              */
/* ------------------------------------------------------------------------- */

t_scene		*create_scene(const char *name);
void		destroy_scene(t_scene *scene);
bool		scene_add_primitive(t_scene *scene, t_prim_params params, 
					t_prim_type type);
bool		scene_add_mesh(t_scene *scene, t_mesh mesh);
int			scene_add_material(t_scene *scene, t_vec3 color);
bool		scene_add_light(t_scene *scene, t_light light);
bool		scene_add_tri(t_scene *scene, t_vec3 v[3], int mat_id);
void		scene_invalidate(t_scene *scene);

#endif


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 23:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "objects.h"

typedef struct s_scene
{
	char							*name;

	t_sphere						*spheres;
	int								sphere_count;
	int								sphere_cap;

	t_plane							*planes;
	int								plane_count;
	int								plane_cap;

	t_cylinder						*cylinders;
	int								cylinder_count;
	int								cylinder_cap;

	t_cone							*cones;
	int								cone_count;
	int								cone_cap;

	t_tri_shape						*triangles;
	int								tri_count;
	int								tri_cap;

	t_rect							*rects;
	int								rect_count;
	int								rect_cap;

	t_pyramid						*pyramids;
	int								pyramid_count;
	int								pyramid_cap;

	t_box							*boxes;
	int								box_count;
	int								box_cap;

	t_capsule						*capsules;
	int								capsule_count;
	int								capsule_cap;

	t_mesh_group					*groups;
	int								group_count;
	int								group_cap;

	t_skinned_mesh					*animated;
	int								anim_count;
	int								anim_cap;

	t_material						*materials;
	int								mat_count;
	int								mat_cap;
	t_ambient						ambient;
	t_camera						camera;
	t_light							*lights;
	int								light_count;
	int								light_cap;

	t_animation						*clips;
	int								clip_count;
	int								clip_cap;
	uint32_t						version;
	void							*mlx;
	t_emissive_ref					*emissive_cache;
	bool							simulate_physics;
}	t_scene;

/* ------------------------------------------------------------------------- */
/*                             SCENE MANAGEMENT                              */
/* ------------------------------------------------------------------------- */

t_scene		*create_scene(const char *name);
void		destroy_scene(t_scene *scene);

/* Scene injection helpers for format-specific models */
bool		scene_add_glb(t_scene *scene, t_glb_model model);
bool		scene_add_fbx(t_scene *scene, t_fbx_model model);

#endif

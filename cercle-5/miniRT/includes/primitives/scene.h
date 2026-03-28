/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:08:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "objects.h"
# include "anim.h"

typedef struct s_emissive_ref
{
	t_type				type;
	int					index;
}						t_emissive_ref;

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

	t_emissive_ref					*emissive_cache;
}	t_scene;

/* ------------------------------------------------------------------------- */
/*                             SCENE MANAGEMENT                              */
/* ------------------------------------------------------------------------- */

t_scene		*create_scene(const char *name);
void		destroy_scene(t_scene *scene);

#endif

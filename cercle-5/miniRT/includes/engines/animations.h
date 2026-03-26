/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:10:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 18:23:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "scene.h"

/* Animation types */
typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}					t_anim_path;

typedef enum e_interpolation
{
	INTERP_STEP,
	INTERP_LINEAR,
	INTERP_CUBIC
}					t_interpolation;

typedef struct s_anim_sampler
{
	float			*inputs;
	float			*outputs;
	int				count;
	t_interpolation	method;
}					t_anim_sampler;

typedef struct s_anim_channel
{
	int				node_idx;
	t_anim_path		path;
	int				sampler_idx;
}					t_anim_channel;

typedef struct s_animation
{
	char			*name;
	t_anim_channel	*channels;
	int				channel_count;
	t_anim_sampler	*samplers;
	int				sampler_count;
	double			max_time;
	double			current_time;
}					t_animation;

/* ── Engine Functions ── */

/**
 * @brief Main entry point for the animation engine.
 * Updates all animated objects in the scene based on delta time.
 * @param scene The scene containing animated objects.
 * @param dt Delta time since last update.
 */
void				update_animations(t_scene *scene, double dt);

/**
 * @brief Updates a single GLB mesh's animation state.
 */
void				glb_update_mesh_anim(t_mesh *mesh, t_scene *scene, double dt);

#endif

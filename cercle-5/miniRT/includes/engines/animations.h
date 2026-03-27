/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:10:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 04:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "scene.h"

/* --- Animation Metadata --- */
typedef enum e_interp_method
{
	INTERP_LINEAR,
	INTERP_STEP,
	INTERP_CUBIC
}	t_interp_method;

typedef enum e_anim_path
{
	PATH_TRANSLATION,
	PATH_ROTATION,
	PATH_SCALE,
	PATH_WEIGHTS
}	t_anim_path;

/* --- Core Animation Structures --- */

typedef struct s_anim_sampler
{
	float			*inputs;
	float			*outputs;
	int				count;
	t_interp_method	method;
}	t_anim_sampler;

typedef struct s_anim_channel
{
	int				sampler_idx;
	int				node_idx;
	t_anim_path		path;
}	t_anim_channel;

typedef struct s_animation
{
	char			*name;
	t_anim_channel	*channels;
	int				channel_count;
	t_anim_sampler	*samplers;
	int				sampler_count;
	double			max_time;
}	t_animation;

typedef struct s_mesh_anim_state
{
	int				current_anim;
	double			current_time;
	t_mat4			*bone_matrices;
	int				bone_count;
}	t_mesh_anim_state;

typedef struct s_anim_state
{
	t_scene				*scene;
	t_mesh_anim_state	*mesh_states;
	int					mesh_count;
}	t_anim_state;

/* --- Engine Functions --- */
void	update_animations(t_scene *scene, double dt);
void	glb_update_mesh_anim(t_mesh *mesh, t_scene *scene, double dt);

#endif

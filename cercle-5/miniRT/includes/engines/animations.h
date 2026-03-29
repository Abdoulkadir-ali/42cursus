/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:10:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:43:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "scene.h"

/* Per-frame runtime state tracked by the animation engine. */
typedef struct s_mesh_anim_state
{
	int		current_anim;
	double	anim_time;
}			t_mesh_anim_state;

/* ------------------------------------------------------------------------- */
/*                             PRIMARY INTERFACE                             */
/* ------------------------------------------------------------------------- */

void		update_animations(t_scene *scene, double dt);
void		update_skinned_mesh(t_skinned_mesh *sm);
void		update_skeleton_hierarchy(t_skinned_mesh *sm);

/* ------------------------------------------------------------------------- */
/*                                 SAMPLING                                  */
/* ------------------------------------------------------------------------- */

int			anim_find_bracket(t_anim_sampler *s, float time, float *t_out);
void		anim_advance_time(t_skinned_mesh *sm, t_animation *clip, float dt);

/* ------------------------------------------------------------------------- */
/*                              INTERPOLATION                                */
/* ------------------------------------------------------------------------- */

t_vec3		anim_interpolate(t_anim_sampler *s, int frame, float t,
				t_anim_path path);
t_vec3		vec3_lerp_clamped(t_vec3 a, t_vec3 b, float t);t_vec3	quat_nlerp(t_vec3 a, t_vec3 b, float t);t_vec3		quat_slerp(t_vec3 a, t_vec3 b, float t);
t_vec3		vec3_step(t_vec3 a, t_vec3 b, float t);
t_mat4		quat_to_mat4(t_vec3 q);

/* ------------------------------------------------------------------------- */
/*                                   POSING                                  */
/* ------------------------------------------------------------------------- */

void		anim_apply_trs_to_bone(t_bone *bone, t_vec3 pos, t_vec3 rot,
				t_vec3 scale);

/* ------------------------------------------------------------------------- */
/*                                   DEBUG                                   */
/* ------------------------------------------------------------------------- */

void		anim_debug_print_skeleton(t_skinned_mesh *sm);

#endif

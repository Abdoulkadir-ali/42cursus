/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:10:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:02:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
# define ANIMATIONS_H

/* All animation/skeletal types come from scene.h -> anim.h.        */
/* Engines include only scene.h. No t_mesh here.                    */
# include "scene.h"

/* Per-frame runtime state tracked by the animation engine.         */
/* Lives in t_rt_engine, NOT in t_scene.                            */
typedef struct s_mesh_anim_state
{
	int		current_anim;
	double	anim_time;
}			t_mesh_anim_state;

/* Engine functions — operate on scene->animated[] and scene->clips[] */
void		update_animations(t_scene *scene, double dt);
void		update_skinned_mesh(t_skinned_mesh *sm);
void		update_skeleton_hierarchy(t_skinned_mesh *sm);

#endif

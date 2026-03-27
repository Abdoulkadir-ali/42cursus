/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 18:10:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 08:47:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
#define ANIMATIONS_H

# include "primitives.h"

typedef struct s_mesh_anim_state
{
	int						current_anim;
	double					current_time;
	t_mat4					*bone_matrices;
	int						bone_count;
}							t_mesh_anim_state;

typedef struct s_anim_state
{
	t_scene					*scene;
	t_mesh_anim_state		*mesh_states;
	int						mesh_count;
}							t_anim_state;


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


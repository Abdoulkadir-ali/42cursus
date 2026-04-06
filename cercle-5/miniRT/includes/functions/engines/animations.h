/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animations.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 15:26:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATIONS_H
# define ANIMATIONS_H

# include "scene.h"
# include "objects.h"
# include "types.h"
# include "debug.h"

char	*animation_mesh_name(t_mesh *m);
void	anim_engine_rebuild_index(t_anim_engine *engine, t_scene *scene);
void	anim_engine_free(t_anim_engine *engine);
bool	update_animation_engine(t_scene *scene, t_anim_engine *engine, double dt);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   particle_emitter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/12 10:57:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "particles.h"

bool	scene_add_emitter_obj(t_scene *scene, t_emitter em)
{
	return (scene_add_emitter(scene, em));
}

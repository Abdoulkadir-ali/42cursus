/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:43:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_box(t_scene *scene, t_parser *p)
{
	t_box	box;
	t_vec3	color;

	ft_memset(&box, 0, sizeof(t_box));
	if (!parse_vec3(p, &box.transform.pos))
		return (false);
	if (!parse_vec3(p, &box.half_extents))
		return (false);
	if (!parse_vec3(p, &color))
		return (false);
	box.mat_id = scene_add_material(scene, color);
	return (scene_add_box(scene, box));
}


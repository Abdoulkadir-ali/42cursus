/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:44:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_rect(t_scene *scene, t_parser *p)
{
	t_rect	rect;
	t_vec3	color;

	ft_memset(&rect, 0, sizeof(t_rect));
	if (!parse_vec3(p, &rect.v[0]) || !parse_vec3(p, &rect.v[1])
		|| !parse_vec3(p, &rect.v[2]) || !parse_vec3(p, &rect.v[3])
		|| !parse_vec3(p, &color))
		return (false);
	rect.transform.pos = vec3_scale(vec3_add(vec3_add(rect.v[0], rect.v[1]),
				vec3_add(rect.v[2], rect.v[3])), 0.25);
	rect.mat_id = scene_add_material(scene, color);
	if (rect.mat_id < 0)
		return (false);
	return (scene_add_rect(scene, rect));
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:22:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static bool	scene_add_rect(t_scene *scene, t_rect rect)
{
	if (!DYNARRAY_ENSURE_INT(&scene->rects, &scene->rect_count,
			&scene->rect_cap, sizeof(t_rect)))
		return (false);
	if (vec3_mag_sq(rect.transform.scale) < SCALE_EPSILON)
		rect.transform.scale = vec3(1, 1, 1);
	scene->rects[scene->rect_count++] = rect;
	return (true);
}

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


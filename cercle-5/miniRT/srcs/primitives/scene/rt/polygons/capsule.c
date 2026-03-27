/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   capsule.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:43:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_capsule(t_scene *scene, t_parser *p)
{
	t_capsule	cp;
	t_vec3		color;

	ft_memset(&cp, 0, sizeof(t_capsule));
	if (!parse_vec3(p, &cp.transform.pos))
		return (false);
	if (!parse_vec3(p, &cp.axis))
		return (false);
	cp.radius = parse_double(p);
	cp.half_height = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	cp.axis = vec3_norm(cp.axis);
	cp.mat_id = scene_add_material(scene, color);
	return (scene_add_capsule(scene, cp));
}

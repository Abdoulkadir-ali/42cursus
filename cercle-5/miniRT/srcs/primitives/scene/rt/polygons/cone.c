/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:43:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_cone(t_scene *scene, t_parser *p)
{
	t_cone	co;
	t_vec3	color;

	ft_memset(&co, 0, sizeof(t_cone));
	if (!parse_vec3(p, &co.transform.pos))
		return (false);
	if (!parse_vec3(p, &co.transform.forward))
		return (false);
	co.radius = parse_double(p) / 2.0;
	co.height = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	co.transform.forward = vec3_norm(co.transform.forward);
	co.mat_id = scene_add_material(scene, color);
	if (co.mat_id < 0)
		return (false);
	return (scene_add_cone(scene, co));
}

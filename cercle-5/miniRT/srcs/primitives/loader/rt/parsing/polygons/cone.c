/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:18:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	parse_cone(t_scene *scene, t_parser *p)
{
	t_prim_params	params;
	t_vec3			color;

	ft_memset(&params, 0, sizeof(t_prim_params));
	if (!parse_vec3(p, &params.pos))
		return (false);
	if (!parse_vec3(p, &params.axis))
		return (false);
	params.radius = (float)parse_double(p) / 2.0f;
	params.height = (float)parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	params.axis = vec3_norm(params.axis);
	params.mat_id = scene_add_material(scene, color);
	return (scene_add_primitive(scene, params, PRIM_CONE));
}

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

#include "loader.h"

bool	parse_rect(t_scene *scene, t_parser *p)
{
	t_prim_params	params;
	t_vec3			v[4];
	t_vec3			color;

	ft_memset(&params, 0, sizeof(t_prim_params));
	if (!parse_vec3(p, &v[0]) || !parse_vec3(p, &v[1])
		|| !parse_vec3(p, &v[2]) || !parse_vec3(p, &v[3])
		|| !parse_vec3(p, &color))
		return (false);
	params.pos = vec3_scale(vec3_add(vec3_add(v[0], v[1]),
				vec3_add(v[2], v[3])), 0.25);
	params.axis = vec3_norm(vec3_cross(vec3_sub(v[1], v[0]), 
				vec3_sub(v[2], v[0])));
	params.extents.x = (float)vec3_mag(vec3_sub(v[1], v[0]));
	params.extents.y = (float)vec3_mag(vec3_sub(v[2], v[0]));
	params.tangent = vec3_norm(vec3_sub(v[1], v[0]));
	params.mat_id = scene_add_material(scene, color);
	return (scene_add_primitive(scene, params, PRIM_RECT));
}


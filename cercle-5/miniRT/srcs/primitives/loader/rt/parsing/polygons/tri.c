/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tri.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 05:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	parse_tri_shape(t_scene *scene, t_parser *p)
{
	t_vec3		v[3];
	t_vec3		color;
	int			mat_id;

	if (!parse_vec3(p, &v[0]) || !parse_vec3(p, &v[1])
		|| !parse_vec3(p, &v[2]) || !parse_vec3(p, &color))
		return (false);
	mat_id = scene_add_material(scene, color);
	return (scene_add_tri(scene, v, mat_id));
}
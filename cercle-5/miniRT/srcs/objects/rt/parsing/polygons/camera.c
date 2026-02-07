/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/rt.h"

t_parse_obj	parse_camera(char **tokens)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	
	if (!parse_vec3_checked(tokens[1], &res.data.camera.pos)
		|| !parse_vec3_checked(tokens[2], &res.data.camera.rotation)
		|| !parse_float_checked(tokens[3], &res.data.camera.fov))
		return (res);
	
	if (vec3_mag_sq(res.data.camera.rotation) == 0.0)
		res.data.camera.rotation = vec3(0, 0, -1);
	else
		res.data.camera.rotation = vec3_norm(res.data.camera.rotation);
	
	res.data.camera.forward = res.data.camera.rotation;
	res.type = TYPE_CAMERA;
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a camera entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
t_parse_obj	parse_camera(char **tokens)
{
	t_parse_obj	res;
	t_vec3		rot_v;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	if (!parse_vec3_checked(tokens[1], &res.data.camera.transform.pos) \
		|| !parse_vec3_checked(tokens[2], &rot_v) \
		|| !parse_float_checked(tokens[3], &res.data.camera.fov))
		return (res);
	if (vec3_mag_sq(rot_v) == 0.0)
		rot_v = vec3(0, 0, -1);
	else
		rot_v = vec3_norm(rot_v);
	res.data.camera.transform.forward = rot_v;
	res.data.camera.transform.rotation.pitch = asin(rot_v.y);
	res.data.camera.transform.rotation.yaw = atan2(rot_v.x, rot_v.z);
	res.type = TYPE_CAMERA;
	return (res);
}

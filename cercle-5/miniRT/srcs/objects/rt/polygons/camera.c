/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a camera entry from tokens.
 *
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
/**
 * Parses a camera entry from the buffered parser.
 */
t_parse_obj	parse_camera(t_parser *p)
{
	t_parse_obj	res = {0};
	t_vec3		rot_v;

	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.camera.transform.pos))
		return (res);
	if (!parse_vec3(p, &rot_v))
		return (res);
	res.data.camera.fov = parse_double(p);
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

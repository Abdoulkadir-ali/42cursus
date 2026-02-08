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
	t_vec3		rot_vec;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	
	if (!parse_vec3_checked(tokens[1], &res.data.camera.transform.pos)
		|| !parse_vec3_checked(tokens[2], &rot_vec)
		|| !parse_float_checked(tokens[3], &res.data.camera.fov))
		return (res);
	
	if (vec3_mag_sq(rot_vec) == 0.0)
		rot_vec = vec3(0, 0, -1);
	else
		rot_vec = vec3_norm(rot_vec);
	
	res.data.camera.transform.forward = rot_vec;
	res.data.camera.transform.rotation.pitch = asin(rot_vec.y);
	res.data.camera.transform.rotation.yaw = atan2(rot_vec.x, rot_vec.z);
	res.type = TYPE_CAMERA;
	return (res);
}

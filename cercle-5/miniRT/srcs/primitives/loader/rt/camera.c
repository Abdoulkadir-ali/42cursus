/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

t_parse_obj	rt_parse_camera_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rot_v;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_CAMERA;
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
	return (res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindrical.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 20:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_parse_obj	rt_parse_cylinder_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		axis;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_CYLINDER;
	if (!parse_vec3(p, &res.data.cylinder.transform.pos))
		return (res);
	if (!parse_vec3(p, &axis))
		return (res);
	res.data.cylinder.radius = parse_double(p);
	res.data.cylinder.height = parse_double(p);
	if (!parse_vec3(p, &res.data.cylinder.temp_color))
		return (res);
	res.data.cylinder.transform.forward = vec3_norm(axis);
	res.data.cylinder.transform.scale = vec3(res.data.cylinder.radius,
			res.data.cylinder.height, res.data.cylinder.radius);
	return (res);
}

t_parse_obj	rt_parse_cone_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		axis;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_CONE;
	if (!parse_vec3(p, &res.data.cone.transform.pos))
		return (res);
	if (!parse_vec3(p, &axis))
		return (res);
	res.data.cone.radius = parse_double(p);
	res.data.cone.height = parse_double(p);
	if (!parse_vec3(p, &res.data.cone.temp_color))
		return (res);
	res.data.cone.transform.forward = vec3_norm(axis);
	res.data.cone.transform.scale = vec3(res.data.cone.radius,
			res.data.cone.height, res.data.cone.radius);
	return (res);
}

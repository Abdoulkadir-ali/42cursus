/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polygons.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

t_parse_obj	rt_parse_tri_shape_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		e1;
	t_vec3		e2;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_TRI;
	if (!parse_vec3(p, &res.data.tri_shape.v[0])
		|| !parse_vec3(p, &res.data.tri_shape.v[1])
		|| !parse_vec3(p, &res.data.tri_shape.v[2])
		|| !parse_vec3(p, &res.data.tri_shape.temp_color))
		return (res);
	e1 = vec3_sub(res.data.tri_shape.v[1], res.data.tri_shape.v[0]);
	e2 = vec3_sub(res.data.tri_shape.v[2], res.data.tri_shape.v[0]);
	res.data.tri_shape.normal = vec3_norm(vec3_cross(e1, e2));
	res.data.tri_shape.transform.pos = vec3_scale(vec3_add(vec3_add(
					res.data.tri_shape.v[0], res.data.tri_shape.v[1]),
				res.data.tri_shape.v[2]), 1.0 / 3.0);
	return (res);
}

t_parse_obj	rt_parse_rect_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		e1;
	t_vec3		e2;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_RECT;
	if (!parse_vec3(p, &res.data.rect.v[0])
		|| !parse_vec3(p, &res.data.rect.v[1])
		|| !parse_vec3(p, &res.data.rect.v[2])
		|| !parse_vec3(p, &res.data.rect.v[3])
		|| !parse_vec3(p, &res.data.rect.temp_color))
		return (res);
	e1 = vec3_sub(res.data.rect.v[1], res.data.rect.v[0]);
	e2 = vec3_sub(res.data.rect.v[3], res.data.rect.v[0]);
	res.data.rect.normal = vec3_norm(vec3_cross(e1, e2));
	res.data.rect.transform.pos = vec3_scale(vec3_add(
				vec3_add(res.data.rect.v[0], res.data.rect.v[1]),
				vec3_add(res.data.rect.v[2], res.data.rect.v[3])), 0.25);
	return (res);
}

t_parse_obj	rt_parse_pyramid_obj(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_PYRAMID;
	if (!parse_vec3(p, &res.data.pyramid.transform.pos)
		|| !parse_vec3(p, &res.data.pyramid.up))
		return (res);
	res.data.pyramid.base_size = parse_double(p);
	res.data.pyramid.height = parse_double(p);
	if (!parse_vec3(p, &res.data.pyramid.temp_color))
		return (res);
	res.data.pyramid.up = vec3_norm(res.data.pyramid.up);
	return (res);
}

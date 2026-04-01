/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:03:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:25:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	init_shape_phys(t_physics_body *phys)
{
	phys->mass = 1.0;
	phys->elasticity = 0.5;
	phys->friction = 0.5;
	phys->is_static = false;
}

t_parse_obj	parse_tri_shape(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		e[2];

	ft_memset(&res, 0, sizeof(res));
	if (!parse_vec3(p, &res.data.tri_shape.v[0])
		|| !parse_vec3(p, &res.data.tri_shape.v[1])
		|| !parse_vec3(p, &res.data.tri_shape.v[2])
		|| !parse_vec3(p, &res.data.tri_shape.temp_color))
		return (res);
	e[0] = vec3_sub(res.data.tri_shape.v[1], res.data.tri_shape.v[0]);
	e[1] = vec3_sub(res.data.tri_shape.v[2], res.data.tri_shape.v[0]);
	res.data.tri_shape.normal = vec3_norm(vec3_cross(e[0], e[1]));
	res.data.tri_shape.xform.pos = vec3_scale(
			vec3_add(vec3_add(res.data.tri_shape.v[0],
					res.data.tri_shape.v[1]), res.data.tri_shape.v[2]),
			1.0 / 3.0);
	init_shape_phys(&res.data.tri_shape.phys);
	res.type = TYPE_TRI;
	return (res);
}

t_parse_obj	parse_rect(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		e[2];

	ft_memset(&res, 0, sizeof(res));
	if (!parse_vec3(p, &res.data.rect.v[0])
		|| !parse_vec3(p, &res.data.rect.v[1])
		|| !parse_vec3(p, &res.data.rect.v[2])
		|| !parse_vec3(p, &res.data.rect.v[3])
		|| !parse_vec3(p, &res.data.rect.temp_color))
		return (res);
	e[0] = vec3_sub(res.data.rect.v[1], res.data.rect.v[0]);
	e[1] = vec3_sub(res.data.rect.v[3], res.data.rect.v[0]);
	res.data.rect.normal = vec3_norm(vec3_cross(e[0], e[1]));
	res.data.rect.transform.pos = vec3_scale(
			vec3_add(vec3_add(res.data.rect.v[0], res.data.rect.v[1]),
				vec3_add(res.data.rect.v[2], res.data.rect.v[3])), 0.25);
	init_shape_phys(&res.data.rect.phys);
	res.type = TYPE_RECT;
	return (res);
}

t_parse_obj	parse_pyramid(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	if (!parse_vec3(p, &res.data.pyramid.transform.pos)
		|| !parse_vec3(p, &res.data.pyramid.up))
		return (res);
	res.data.pyramid.base_size = parse_double(p);
	res.data.pyramid.height = parse_double(p);
	if (!parse_vec3(p, &res.data.pyramid.temp_color))
		return (res);
	res.data.pyramid.up = vec3_norm(res.data.pyramid.up);
	init_shape_phys(&res.data.pyramid.phys);
	res.type = TYPE_PYRAMID;
	return (res);
}

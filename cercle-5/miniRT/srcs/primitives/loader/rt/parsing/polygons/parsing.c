/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:56:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "debug.h"

bool	parse_camera(t_rt_buf *buf, t_parser *p)
{
	t_transform	t;
	double		fov;

	ft_memset(&t, 0, sizeof(t_transform));
	if (!parse_vec3(p, &t.pos) || !parse_vec3(p, &t.forward))
		return (false);
	fov = parse_double(p);
	if (fov <= 0.0 || fov >= 180.0)
		return (false);
	buf->camera.transform = t;
	buf->camera.fov = fov;
	buf->has_camera = true;
	return (true);
}

/*
** Parses position + per-type fields into a t_rt_shape transient, validates,
** then pushes into buf->shapes. No scene is touched here.
*/
static bool	buf_push_shape(t_rt_buf *buf, t_rt_shape *shape)
{
	t_rt_shape	*tmp;

	if (buf->shape_count >= buf->shape_cap)
	{
		buf->shape_cap = (buf->shape_cap == 0) ? 64 : buf->shape_cap * 2;
		tmp = realloc(buf->shapes, buf->shape_cap * sizeof(t_rt_shape));
		if (!tmp)
			return (false);
		buf->shapes = tmp;
	}
	DBG_TRACE_MSG(DBG_CH_PARSER, "buf push type=%d [%zu]\n",
		shape->type, buf->shape_count);
	buf->shapes[buf->shape_count++] = *shape;
	return (true);
}

static bool	parse_common_prim(t_rt_buf *buf, t_parser *p, t_prim_type type)
{
	t_rt_shape	shape;

	ft_memset(&shape, 0, sizeof(t_rt_shape));
	shape.type = type;
	if (!parse_vec3(p, &shape.params.pos))
		return (false);
	if (type != PRIM_SPHERE)
	{
		if (!parse_vec3(p, &shape.params.axis))
			return (false);
		shape.params.axis = vec3_norm(shape.params.axis);
	}
	if (type == PRIM_RECT)
	{
		if (!parse_vec3(p, &shape.params.tangent))
			return (false);
		shape.params.tangent = vec3_norm(shape.params.tangent);
	}
	if (type == PRIM_SPHERE)
	{
		shape.params.radius = (float)(parse_double(p) / 2.0);
		if (shape.params.radius <= 0.0f)
			return (false);
	}
	if (type == PRIM_CYLINDER || type == PRIM_CONE || type == PRIM_CAPSULE)
	{
		if (type != PRIM_CAPSULE)
			shape.params.radius = (float)(parse_double(p) / 2.0f);
		else
			shape.params.radius = (float)parse_double(p);
		shape.params.height = (float)parse_double(p);
		if (shape.params.radius <= 0.0f || shape.params.height <= 0.0f)
			return (false);
	}
	if (type == PRIM_BOX)
	{
		if (!parse_vec3(p, &shape.params.extents))
			return (false);
	}
	if (type == PRIM_RECT)
	{
		if (!parse_vec2(p, (t_vec2 *)&shape.params.extents))
			return (false);
	}
	if (type == PRIM_PYRAMID)
	{
		shape.params.radius = (float)parse_double(p);
		shape.params.height = (float)parse_double(p);
		if (shape.params.radius <= 0.0f || shape.params.height <= 0.0f)
			return (false);
	}
	if (!parse_vec3(p, &shape.color))
		return (false);
	return (buf_push_shape(buf, &shape));
}

bool	parse_sphere(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_SPHERE));
}

bool	parse_plane(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_PLANE));
}

bool	parse_cylinder(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_CYLINDER));
}

bool	parse_cone(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_CONE));
}

bool	parse_box(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_BOX));
}

bool	parse_rect(t_rt_buf *buf, t_parser *p)
{
	t_rt_shape	shape;
	t_vec3		v[4];
	t_vec3		e0;
	t_vec3		e1;

	ft_memset(&shape, 0, sizeof(t_rt_shape));
	shape.type = PRIM_RECT;
	if (!parse_vec3(p, &v[0]) || !parse_vec3(p, &v[1])
		|| !parse_vec3(p, &v[2]) || !parse_vec3(p, &v[3]))
		return (false);
	if (!parse_vec3(p, &shape.color))
		return (false);
	e0 = vec3_sub(v[1], v[0]);
	e1 = vec3_sub(v[3], v[0]);
	shape.params.extents.x = (float)(vec3_mag(e0) * 0.5);
	shape.params.extents.y = (float)(vec3_mag(e1) * 0.5);
	if (shape.params.extents.x < 1e-6f || shape.params.extents.y < 1e-6f)
		return (false);
	shape.params.axis = vec3_norm(vec3_cross(e0, e1));
	shape.params.pos = vec3_scale(vec3_add(vec3_add(v[0], v[1]),
				vec3_add(v[2], v[3])), 0.25f);
	return (buf_push_shape(buf, &shape));
}

bool	parse_capsule(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_CAPSULE));
}

bool	parse_pyramid(t_rt_buf *buf, t_parser *p)
{
	return (parse_common_prim(buf, p, PRIM_PYRAMID));
}

bool	parse_tri_shape(t_rt_buf *buf, t_parser *p)
{
	t_rt_shape	shape;
	t_vec3		e1;
	t_vec3		e2;

	ft_memset(&shape, 0, sizeof(t_rt_shape));
	shape.type = PRIM_TRIANGLE;
	if (!parse_vec3(p, &shape.data.tri[0]) || !parse_vec3(p, &shape.data.tri[1])
		|| !parse_vec3(p, &shape.data.tri[2]) || !parse_vec3(p, &shape.color))
		return (false);
	e1 = vec3_sub(shape.data.tri[1], shape.data.tri[0]);
	e2 = vec3_sub(shape.data.tri[2], shape.data.tri[0]);
	if (vec3_mag(vec3_cross(e1, e2)) < 1e-9)
		return (false);
	return (buf_push_shape(buf, &shape));
}

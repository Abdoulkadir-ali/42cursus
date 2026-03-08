#include "objects.h"

t_parse_obj	parse_tri_shape(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;
	t_vec3		e1;
	t_vec3		e2;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.tri_shape.v[0]))
		return (res);
	if (!parse_vec3(p, &res.data.tri_shape.v[1]))
		return (res);
	if (!parse_vec3(p, &res.data.tri_shape.v[2]))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.tri_shape.temp_color = rgb;
	e1 = vec3_sub(res.data.tri_shape.v[1], res.data.tri_shape.v[0]);
	e2 = vec3_sub(res.data.tri_shape.v[2], res.data.tri_shape.v[0]);
	res.data.tri_shape.normal = vec3_norm(vec3_cross(e1, e2));
	res.type = TYPE_TRI;
	return (res);
}

t_parse_obj	parse_rect_shape(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.rect_parse.v[0]))
		return (res);
	if (!parse_vec3(p, &res.data.rect_parse.v[1]))
		return (res);
	if (!parse_vec3(p, &res.data.rect_parse.v[2]))
		return (res);
	if (!parse_vec3(p, &res.data.rect_parse.v[3]))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.rect_parse.temp_color = rgb;
	res.type = TYPE_RECT;
	return (res);
}

t_parse_obj	parse_pyramid(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.pyramid_parse.center))
		return (res);
	if (!parse_vec3(p, &res.data.pyramid_parse.up))
		return (res);
	res.data.pyramid_parse.base_size = parse_double(p);
	res.data.pyramid_parse.height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.pyramid_parse.temp_color = rgb;
	res.data.pyramid_parse.up = vec3_norm(res.data.pyramid_parse.up);
	res.type = TYPE_PYRAMID;
	return (res);
}

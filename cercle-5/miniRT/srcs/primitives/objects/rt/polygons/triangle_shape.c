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
	    res.data.tri_shape.transform.pos = vec3_scale(
		    vec3_add(vec3_add(res.data.tri_shape.v[0],
			    res.data.tri_shape.v[1]), res.data.tri_shape.v[2]),
		    1.0 / 3.0);
	    /* physics: properties will be applied by the physics system during bake */
	res.type = TYPE_TRI;
	return (res);
}

t_parse_obj	parse_rect(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;
	t_vec3		e1;
	t_vec3		e2;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	ft_memset(&res.data.rect, 0, sizeof(res.data.rect));
	if (!parse_vec3(p, &res.data.rect.v[0]))
		return (res);
	if (!parse_vec3(p, &res.data.rect.v[1]))
		return (res);
	if (!parse_vec3(p, &res.data.rect.v[2]))
		return (res);
	if (!parse_vec3(p, &res.data.rect.v[3]))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.rect.temp_color = rgb;
	e1 = vec3_sub(res.data.rect.v[1], res.data.rect.v[0]);
	e2 = vec3_sub(res.data.rect.v[3], res.data.rect.v[0]);
	res.data.rect.normal = vec3_norm(vec3_cross(e1, e2));
	res.data.rect.transform.pos = vec3_scale(
			vec3_add(vec3_add(res.data.rect.v[0], res.data.rect.v[1]),
				vec3_add(res.data.rect.v[2], res.data.rect.v[3])), 0.25);
	/* physics: properties will be applied by the physics system during bake */
	res.type = TYPE_RECT;
	return (res);
}

t_parse_obj	parse_pyramid(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	ft_memset(&res.data.pyramid, 0, sizeof(res.data.pyramid));
	if (!parse_vec3(p, &res.data.pyramid.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.pyramid.up))
		return (res);
	res.data.pyramid.base_size = parse_double(p);
	res.data.pyramid.height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.pyramid.temp_color = rgb;
	res.data.pyramid.up = vec3_norm(res.data.pyramid.up);
	/* physics: properties will be applied by the physics system during bake */
	res.type = TYPE_PYRAMID;
	return (res);
}

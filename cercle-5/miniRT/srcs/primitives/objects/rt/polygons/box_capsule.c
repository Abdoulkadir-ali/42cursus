#include "objects.h"

t_parse_obj	parse_box(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	ft_memset(&res.data.box, 0, sizeof(res.data.box));
	if (!parse_vec3(p, &res.data.box.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.box.transform.forward))
		return (res);
	if (vec3_mag_sq(res.data.box.transform.forward) > 1e-6)
		res.data.box.transform.forward = vec3_norm(
				res.data.box.transform.forward);
	else
		res.data.box.transform.forward = vec3(1, 0, 0);
	if (!parse_vec3(p, &res.data.box.half_extents))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.box.temp_color = rgb;
	res.data.box.transform.scale = res.data.box.half_extents;
	/* physics: properties will be set by the physics system during bake */
	res.type = TYPE_BOX;
	return (res);
}

t_parse_obj	parse_capsule(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res = (t_parse_obj){0};
	res.type = TYPE_NONE;
	ft_memset(&res.data.capsule, 0, sizeof(res.data.capsule));
	if (!parse_vec3(p, &res.data.capsule.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.capsule.axis))
		return (res);
	if (vec3_mag_sq(res.data.capsule.axis) > 1e-6)
		res.data.capsule.axis = vec3_norm(res.data.capsule.axis);
	else
		res.data.capsule.axis = vec3(0, 1, 0);
	res.data.capsule.radius = parse_double(p);
	res.data.capsule.half_height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.capsule.temp_color = rgb;
	    res.data.capsule.transform.scale = vec3(res.data.capsule.radius,
		    res.data.capsule.half_height, res.data.capsule.radius);
	    /* physics: properties will be set by the physics system during bake */
	res.type = TYPE_CAPSULE;
	return (res);
}

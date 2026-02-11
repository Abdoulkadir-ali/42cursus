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

static bool	parse_base(t_parser *p, t_cylinder *out)
{
	double	diameter;
	double	height;
	t_vec3	rgb;

	if (!parse_vec3(p, &out->transform.pos))
		return (false);
	if (!parse_vec3(p, &out->transform.forward))
		return (false);
	diameter = parse_double(p);
	height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (false);
	if (vec3_mag_sq(out->transform.forward) == 0.0)
		out->transform.forward = vec3(0, 1, 0);
	else
		out->transform.forward = vec3_norm(out->transform.forward);
	out->transform.scale = vec3(diameter / 2.0, height, diameter / 2.0);
	out->mat_id = 0;
	out->temp_color = rgb;
	return (true);
}

t_parse_obj	parse_cylinder(t_parser *p)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	if (parse_base(p, &res.data.cylinder))
		res.type = TYPE_CYLINDER;
	return (res);
}

t_parse_obj	parse_cone(t_parser *p)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	/* t_cone layout matches t_cylinder, so cast is safe */
	if (parse_base(p, (t_cylinder *)&res.data.cone))
		res.type = TYPE_CONE;
	return (res);
}

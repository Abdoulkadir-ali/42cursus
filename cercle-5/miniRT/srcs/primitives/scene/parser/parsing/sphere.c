/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * Parses a sphere entry from the buffered parser.
 */
t_parse_obj	parse_sphere(t_parser *p)
{
	t_parse_obj	res;
	double		diameter;
	t_vec3		rgb;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.sphere.transform.pos))
		return (res);
	diameter = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.sphere.radius_sq = (diameter / 2.0) * (diameter / 2.0);
	res.data.sphere.mat_id = 0;
	res.data.sphere.temp_color = rgb;
	res.data.sphere.transform.scale = vec3(1, 1, 1);
	res.data.sphere.inv_scale = vec3(1, 1, 1);
	res.type = TYPE_SPHERE;
	return (res);
}

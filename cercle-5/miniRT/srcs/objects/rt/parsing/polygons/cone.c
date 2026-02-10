/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a cone entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
/**
 * Parses a cone entry from the buffered parser.
 */
t_parse_obj	parse_cone(t_parser *p)
{
	t_parse_obj	res;
	double		diameter;
	double		height;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.cone.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.cone.transform.forward))
		return (res);
	diameter = parse_double(p);
	height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	if (vec3_mag_sq(res.data.cone.transform.forward) == 0.0)
		res.data.cone.transform.forward = vec3(0, 1, 0);
	else
		res.data.cone.transform.forward = \
			vec3_norm(res.data.cone.transform.forward);
	res.data.cone.transform.scale = vec3(diameter / 2.0, height, \
		diameter / 2.0);
	res.data.cone.mat_id = 0;
	res.data.cone.temp_color = rgb;
	res.type = TYPE_CONE;
	return (res);
}

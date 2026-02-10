/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a cylinder entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
/**
 * Parses a cylinder entry from the buffered parser.
 */
t_parse_obj	parse_cylinder(t_parser *p)
{
	t_parse_obj	res;
	double		diameter;
	double		height;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.cylinder.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.cylinder.transform.forward))
		return (res);
	diameter = parse_double(p);
	height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (res);
	if (vec3_mag_sq(res.data.cylinder.transform.forward) == 0.0)
		res.data.cylinder.transform.forward = vec3(0, 1, 0);
	else
		res.data.cylinder.transform.forward = \
			vec3_norm(res.data.cylinder.transform.forward);
	res.data.cylinder.transform.scale = vec3(diameter / 2.0, height, \
		diameter / 2.0);
	res.data.cylinder.mat_id = 0;
	res.data.cylinder.temp_color = rgb;
	res.type = TYPE_CYLINDER;
	return (res);
}

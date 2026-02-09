/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a plane entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
t_parse_obj	parse_plane(char **tokens)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	if (!parse_vec3_checked(tokens[1], &res.data.plane.transform.pos) \
		|| !parse_vec3_checked(tokens[2], &res.data.plane.transform.forward) \
		|| !parse_color_checked(tokens[3], &rgb))
		return (res);
	if (vec3_mag_sq(res.data.plane.transform.forward) == 0.0)
		res.data.plane.transform.forward = vec3(0, 1, 0);
	else
		res.data.plane.transform.forward = \
			vec3_norm(res.data.plane.transform.forward);
	res.data.plane.mat_id = 0;
	res.data.plane.temp_color = rgb;
	res.type = TYPE_PLANE;
	return (res);
}

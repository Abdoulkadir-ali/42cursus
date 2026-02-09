/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a point light entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
t_parse_obj	parse_light(char **tokens)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2])
		return (res);
	if (!parse_vec3_checked(tokens[1], &res.data.light.transform.pos) \
		|| !parse_float_checked(tokens[2], &res.data.light.brightness))
		return (res);
	res.data.light.type = LIGHT_POINT;
	res.data.light.rgb = vec3(255, 255, 255);
	if (tokens[3])
	{
		if (!parse_color_checked(tokens[3], &res.data.light.rgb))
			return (res);
	}
	res.type = TYPE_LIGHT;
	return (res);
}

/**
 * Parses a spot light entry from tokens.
 * 
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
t_parse_obj	parse_spot_light(char **tokens)
{
	t_parse_obj	res;
	double		fov;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (res);
	res.data.light.type = LIGHT_SPOT;
	if (!parse_vec3_checked(tokens[1], &res.data.light.transform.pos) \
		|| !parse_vec3_checked(tokens[2], &res.data.light.transform.forward) \
		|| !parse_float_checked(tokens[3], &res.data.light.brightness) \
		|| !parse_float_checked(tokens[4], &fov))
		return (res);
	res.data.light.transform.forward = \
		vec3_norm(res.data.light.transform.forward);
	res.data.light.cutoff = cos((fov * M_PI / 180.0) / 2.0);
	res.data.light.rgb = vec3(255, 255, 255);
	if (tokens[5])
	{
		if (!parse_color_checked(tokens[5], &res.data.light.rgb))
			return (res);
	}
	res.type = TYPE_LIGHT;
	return (res);
}

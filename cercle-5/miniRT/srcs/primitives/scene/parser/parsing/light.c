/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * Parses a point light entry from tokens.
 *
 * @param tokens The array of strings.
 * @return The parsed object data.
 */
/**
 * Parses a point light entry from the buffered parser.
 */
t_parse_obj	parse_light(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.light.transform.pos))
		return (res);
	res.data.light.brightness = parse_double(p);
	res.data.light.type = LIGHT_POINT;
	res.data.light.rgb = vec3(255, 255, 255);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &res.data.light.rgb);
	res.type = TYPE_LIGHT;
	return (res);
}

/**
 * Parses a spot light entry from the buffered parser.
 */
t_parse_obj	parse_spot_light(t_parser *p)
{
	t_parse_obj	res;
	double		fov;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	res.data.light.type = LIGHT_SPOT;
	if (!parse_vec3(p, &res.data.light.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.light.transform.forward))
		return (res);
	res.data.light.brightness = parse_double(p);
	fov = parse_double(p);
	res.data.light.transform.forward
		= vec3_norm(res.data.light.transform.forward);
	res.data.light.cutoff
		= cos((fov * M_PI / 180.0) / 2.0);
	res.data.light.rgb = vec3(255, 255, 255);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &res.data.light.rgb);
	res.type = TYPE_LIGHT;
	return (res);
}

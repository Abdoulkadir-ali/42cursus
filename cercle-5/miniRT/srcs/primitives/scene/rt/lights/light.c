/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 21:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_light(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_light_obj(p);
	if (parsed.type != TYPE_LIGHT)
		return (false);
	return (scene_add_light(scene, parsed.data.light));
}

bool	parse_ambient(t_scene *scene, t_parser *p)
{
	t_parse_obj	parsed;

	parsed = rt_parse_ambient_obj(p);
	if (parsed.type != TYPE_AMBIENT)
		return (false);
	return (scene_add_ambient(scene, parsed.data.ambient.brightness,
			parsed.data.ambient.rgb));
}

bool	parse_spot_light(t_scene *scene, t_parser *p)
{
	t_light	light;
	double	fov;

	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_SPOT;
	if (!parse_vec3(p, &light.transform.pos))
		return (false);
	if (!parse_vec3(p, &light.transform.forward))
		return (false);
	light.brightness = parse_double(p);
	fov = parse_double(p);
	light.transform.forward = vec3_norm(light.transform.forward);
	light.cutoff = cos((fov * M_PI / 180.0) / 2.0);
	light.rgb = vec3(255, 255, 255);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &light.rgb);
	return (scene_add_light(scene, light));
}

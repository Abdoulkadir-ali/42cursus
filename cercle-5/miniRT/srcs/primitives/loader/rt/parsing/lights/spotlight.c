/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:19:04 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 16:21:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	parse_spot_light(t_scene *scene, t_parser *p)
{
	t_light light;
	double fov;

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
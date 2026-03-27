/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_parse_obj	rt_parse_light_obj(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_LIGHT;
	if (!parse_vec3(p, &res.data.light.transform.pos))
		return (res);
	res.data.light.brightness = parse_double(p);
	res.data.light.type = LIGHT_POINT;
	res.data.light.rgb = vec3(255, 255, 255);
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &res.data.light.rgb);
	return (res);
}

t_parse_obj	rt_parse_ambient_obj(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_AMBIENT;
	res.data.ambient.brightness = parse_double(p);
	if (!parse_vec3(p, &res.data.ambient.rgb))
		return (res);
	return (res);
}

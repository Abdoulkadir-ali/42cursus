/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 06:32:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static bool	buf_push_light(t_rt_buf *buf, t_light *light)
{
	t_light	*tmp;

	if (buf->light_count >= buf->light_cap)
	{
		buf->light_cap = (buf->light_cap == 0) ? 16 : buf->light_cap * 2;
		tmp = realloc(buf->lights, buf->light_cap * sizeof(t_light));
		if (!tmp)
			return (false);
		buf->lights = tmp;
	}
	buf->lights[buf->light_count++] = *light;
	return (true);
}

bool	parse_ambient(t_rt_buf *buf, t_parser *p)
{
	double	brightness;
	t_vec3	rgb;

	if (!parse_double_checked(p, &brightness) || !parse_vec3(p, &rgb))
		return (false);
	buf->ambient.brightness = brightness;
	buf->ambient.rgb = rgb;
	buf->has_ambient = true;
	return (true);
}

bool	parse_light(t_rt_buf *buf, t_parser *p)
{
	t_light	light;

	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_POINT;
	if (!parse_vec3(p, &light.transform.pos))
		return (false);
	light.brightness = parse_double(p);
	light.rgb = (t_vec3){255.0, 255.0, 255.0, 0.0};
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &light.rgb);
	return (buf_push_light(buf, &light));
}

bool	parse_spot_light(t_rt_buf *buf, t_parser *p)
{
	t_light	light;
	double	fov;

	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_SPOT;
	if (!parse_vec3(p, &light.transform.pos) || !parse_vec3(p, &light.transform.forward))
		return (false);
	light.brightness = parse_double(p);
	fov = parse_double(p);
	light.transform.forward = vec3_norm(light.transform.forward);
	light.cutoff = cos((fov * M_PI / 180.0) / 2.0);
	light.rgb = (t_vec3){255.0, 255.0, 255.0, 0.0};
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &light.rgb);
	return (buf_push_light(buf, &light));
}

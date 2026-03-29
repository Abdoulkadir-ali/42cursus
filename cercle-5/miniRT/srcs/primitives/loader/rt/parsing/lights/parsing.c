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
#include "debug.h"

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
	{
		DBG_ERR_MSG(DBG_CH_PARSER, "parse_ambient: FAILED\n");
		return (false);
	}
	buf->ambient.brightness = brightness;
	buf->ambient.rgb = rgb;
	buf->has_ambient = true;
	DBG_INFO_MSG(DBG_CH_PARSER,
		"parse_ambient: bright=%.3f rgb=(%.0f,%.0f,%.0f)\n",
		buf->ambient.brightness, buf->ambient.rgb.x,
		buf->ambient.rgb.y, buf->ambient.rgb.z);
	return (true);
}

bool	parse_light(t_rt_buf *buf, t_parser *p)
{
	t_light	light;

	ft_memset(&light, 0, sizeof(t_light));
	light.type = LIGHT_POINT;
	if (!parse_vec3(p, &light.transform.pos))
	{
		DBG_ERR_MSG(DBG_CH_PARSER, "parse_light: FAILED\n");
		return (false);
	}
	light.brightness = parse_double(p);
	light.rgb = (t_vec3){255.0, 255.0, 255.0, 0.0};
	parser_skip_spaces(p);
	if (parser_peek(p) && parser_peek(p) != '\n')
		parse_vec3(p, &light.rgb);
	if (!buf_push_light(buf, &light))
		return (false);
	DBG_INFO_MSG(DBG_CH_PARSER,
		"parse_light: pos=(%.2f,%.2f,%.2f) bright=%.2f\n",
		light.transform.pos.x, light.transform.pos.y,
		light.transform.pos.z, light.brightness);
	return (true);
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

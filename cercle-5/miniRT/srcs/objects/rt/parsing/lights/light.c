/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/rt.h"

t_parse_obj	parse_light(char **tokens)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2])
		return (res);
	
	if (!parse_vec3_checked(tokens[1], &res.data.light.transform.pos)
		|| !parse_float_checked(tokens[2], &res.data.light.brightness))
		return (res);
	
	res.data.light.type = LIGHT_POINT;
	
	if (tokens[3])
	{
		if (!parse_color_checked(tokens[3], &res.data.light.rgb))
			return (res);
	}
	else
		res.data.light.rgb = vec3(255, 255, 255);
	
	res.type = TYPE_LIGHT;
	return (res);
}

t_parse_obj	parse_spot_light(char **tokens)
{
	t_parse_obj	res;
	double		fov;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3] || !tokens[4])
		return (res);
	
	res.data.light.type = LIGHT_SPOT;
	if (!parse_vec3_checked(tokens[1], &res.data.light.transform.pos)
		|| !parse_vec3_checked(tokens[2], &res.data.light.transform.forward)
		|| !parse_float_checked(tokens[3], &res.data.light.brightness)
		|| !parse_float_checked(tokens[4], &fov))
		return (res);
	
	res.data.light.transform.forward = vec3_norm(res.data.light.transform.forward);
	res.data.light.cutoff = cos((fov * M_PI / 180.0) / 2.0); // Half angle cosine

	if (tokens[5])
	{
		if (!parse_color_checked(tokens[5], &res.data.light.rgb))
			return (res);
	}
	else
		res.data.light.rgb = vec3(255, 255, 255);
	
	res.type = TYPE_LIGHT;
	return (res);
}

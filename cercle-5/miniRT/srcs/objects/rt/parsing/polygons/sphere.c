/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/rt.h"

t_parse_obj	parse_sphere(char **tokens)
{
	t_parse_obj	res;
	double		diameter;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	
	if (!parse_vec3_checked(tokens[1], &res.data.sphere.pos)
		|| !parse_float_checked(tokens[2], &diameter)
		|| !parse_color_checked(tokens[3], &rgb))
		return (res);
	
	res.data.sphere.radius_sq = (float)((diameter / 2.0) * (diameter / 2.0));
	res.data.sphere.mat_id = 0; // Will be set by adder
	res.data.sphere.temp_color = rgb;
	res.type = TYPE_SPHERE;

	return (res);
}

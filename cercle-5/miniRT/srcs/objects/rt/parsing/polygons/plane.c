/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/rt.h"

t_parse_obj	parse_plane(char **tokens)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2] || !tokens[3])
		return (res);
	
	if (!parse_vec3_checked(tokens[1], &res.data.plane.pos)
		|| !parse_vec3_checked(tokens[2], &res.data.plane.normal)
		|| !parse_color_checked(tokens[3], &rgb))
		return (res);
	
	if (vec3_mag_sq(res.data.plane.normal) == 0.0)
		res.data.plane.normal = vec3(0, 1, 0);
	else
		res.data.plane.normal = vec3_norm(res.data.plane.normal);
		
	res.data.plane.mat_id = 0;
	res.data.plane.temp_color = rgb;
	res.type = TYPE_PLANE;

	return (res);
}

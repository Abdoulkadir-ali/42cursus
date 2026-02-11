/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/**
 * Parses a plane entry from the buffered parser.
 */
t_parse_obj	parse_plane(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.plane.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.plane.transform.forward))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	if (vec3_mag_sq(res.data.plane.transform.forward) == 0.0)
		res.data.plane.transform.forward = vec3(0, 1, 0);
	else
		res.data.plane.transform.forward = \
			vec3_norm(res.data.plane.transform.forward);
	res.data.plane.mat_id = 0;
	res.data.plane.temp_color = rgb;
	res.type = TYPE_PLANE;
	return (res);
}

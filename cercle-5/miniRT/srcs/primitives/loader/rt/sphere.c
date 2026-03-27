/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

/**
 * @brief Parses a sphere object from RT content.
 * Follows Rule 1: Object is unaware of Scene.
 * Returns a t_parse_obj union containing the sphere and its temp color.
 */
t_parse_obj	rt_parse_sphere_obj(t_parser *p)
{
	t_parse_obj	res;
	double		diameter;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_SPHERE;
	if (!parse_vec3(p, &res.data.sphere.transform.pos))
		return (res);
	diameter = parse_double(p);
	if (!parse_vec3(p, &res.data.sphere.temp_color))
		return (res);
	res.data.sphere.radius_sq = (diameter / 2.0) * (diameter / 2.0);
	res.data.sphere.radius = (diameter / 2.0);
	return (res);
}

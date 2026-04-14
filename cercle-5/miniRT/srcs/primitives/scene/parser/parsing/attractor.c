/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 12:16:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

/**
 * @brief Parses a gravitational attractor: bh <pos> <mass>
 */
t_parse_obj	parse_attractor(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.attractor.pos))
		return (res);
	res.data.attractor.mass = parse_double(p);
	res.type = TYPE_ATTRACTOR;
	return (res);
}

/**
 * @brief Parses a black hole: bhole <pos> <mass>
 *        Same as attractor but sets is_black_hole=true so the raytracer
 *        performs geodesic (lensing) ray marching near it.
 */
t_parse_obj	parse_black_hole(t_parser *p)
{
	t_parse_obj	res;

	res = parse_attractor(p);
	if (res.type == TYPE_ATTRACTOR)
		res.data.attractor.is_black_hole = true;
	return (res);
}

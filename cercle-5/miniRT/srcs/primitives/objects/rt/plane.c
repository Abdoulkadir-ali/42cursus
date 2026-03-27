/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 21:05:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_parse_obj	rt_parse_plane_obj(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		norm;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_PLANE;
	if (!parse_vec3(p, &res.data.plane.transform.pos))
		return (res);
	if (!parse_vec3(p, &norm))
		return (res);
	if (!parse_vec3(p, &res.data.plane.temp_color))
		return (res);
	res.data.plane.transform.forward = vec3_norm(norm);
	return (res);
}

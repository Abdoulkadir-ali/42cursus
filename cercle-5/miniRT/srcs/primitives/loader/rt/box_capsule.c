/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_capsule.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 23:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 00:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

t_parse_obj	rt_parse_box_obj(t_parser *p)
{
	t_parse_obj	res;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_BOX;
	if (!parse_vec3(p, &res.data.box.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.box.transform.scale))
		return (res);
	if (!parse_vec3(p, &res.data.box.temp_color))
		return (res);
	return (res);
}

t_parse_obj	rt_parse_capsule_obj(t_parser *p)
{
	t_parse_obj	res;
	double		h;
	double		r;

	ft_memset(&res, 0, sizeof(t_parse_obj));
	res.type = TYPE_CAPSULE;
	if (!parse_vec3(p, &res.data.capsule.transform.pos))
		return (res);
	h = parse_double(p);
	r = parse_double(p);
	if (!parse_vec3(p, &res.data.capsule.temp_color))
		return (res);
	res.data.capsule.half_height = h / 2.0;
	res.data.capsule.radius = r;
	return (res);
}

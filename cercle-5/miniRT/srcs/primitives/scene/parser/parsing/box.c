/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:03:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 19:25:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_parse_obj	parse_box(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.box.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.box.half_extents))
		return (res);
	if (!parse_vec3(p, &rgb))
		return (res);
	res.data.box.temp_color = rgb;
	init_poly_phys(&res.data.box.phys);
	res.type = TYPE_BOX;
	return (res);
}

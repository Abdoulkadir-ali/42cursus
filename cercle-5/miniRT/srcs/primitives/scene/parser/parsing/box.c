/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:03:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 18:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	set_box_phys(t_box *box)
{
	init_poly_phys(&box->phys);
	box->phys.center = box->transform.pos;
	box->phys.pos = box->transform.pos;
}

t_parse_obj	parse_box(t_parser *p)
{
	t_parse_obj	res;
	t_vec3		rgb;

	ft_memset(&res, 0, sizeof(res));
	res.type = TYPE_NONE;
	if (!parse_vec3(p, &res.data.box.transform.pos))
		return (res);
	if (!parse_vec3(p, &res.data.box.transform.forward))
		return (res);
	if (vec3_mag_sq(res.data.box.transform.forward) > 1e-6)
		res.data.box.transform.forward
			= vec3_norm(res.data.box.transform.forward);
	else
		res.data.box.transform.forward = vec3(1, 0, 0);
	if (!parse_vec3(p, &res.data.box.half_extents) || !parse_vec3(p, &rgb))
		return (res);
	res.data.box.temp_color = rgb;
	res.data.box.ax[0] = res.data.box.transform.forward;
	vec3_orthonormal_basis(res.data.box.ax[0],
		&res.data.box.ax[1], &res.data.box.ax[2]);
	res.data.box.ax_fwd_cache = res.data.box.ax[0];
	set_box_phys(&res.data.box);
	res.type = TYPE_BOX;
	return (res);
}

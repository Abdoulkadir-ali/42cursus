/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 18:19:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	init_poly_phys(t_physics_body *phys)
{
	phys->mass = 1.0;
	phys->elasticity = 0.5;
	phys->friction = 0.5;
	phys->is_static = false;
}

bool	parse_cylinder_base(t_parser *p, t_cylinder *out)
{
	double	diameter;
	double	height;
	t_vec3	rgb;

	if (!parse_vec3(p, &out->transform.pos))
		return (false);
	if (!parse_vec3(p, &out->transform.forward))
		return (false);
	diameter = parse_double(p);
	height = parse_double(p);
	if (!parse_vec3(p, &rgb))
		return (false);
	if (vec3_mag_sq(out->transform.forward) == 0.0)
		out->transform.forward = vec3(0, 1, 0);
	else
		out->transform.forward = vec3_norm(out->transform.forward);
	out->transform.scale = vec3(diameter / 2.0, height, diameter / 2.0);
	out->mat_id = 0;
	out->temp_color = rgb;
	init_poly_phys(&out->phys);
	return (true);
}

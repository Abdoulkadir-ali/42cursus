/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 14:44:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

bool	parse_cylinder(t_scene *scene, t_parser *p)
{
	t_cylinder	cy;
	t_vec3		color;

	ft_memset(&cy, 0, sizeof(t_cylinder));
	if (!parse_vec3(p, &cy.transform.pos))
		return (false);
	if (!parse_vec3(p, &cy.transform.forward))
		return (false);
	cy.radius = parse_double(p) / 2.0;
	cy.height = parse_double(p);
	if (!parse_vec3(p, &color))
		return (false);
	cy.transform.forward = vec3_norm(cy.transform.forward);
	cy.mat_id = scene_add_material(scene, color);
	if (cy.mat_id < 0)
		return (false);
	return (scene_add_cylinder(scene, cy));
}

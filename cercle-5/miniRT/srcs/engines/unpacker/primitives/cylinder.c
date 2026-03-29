/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_cylinder	unpack_cylinder(const t_primitive_array *p, int i)
{
	t_cylinder	cy;

	ft_memset(&cy, 0, sizeof(cy));
	if (i < 0 || (size_t)i >= p->count)
		return (cy);
	cy.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	cy.axis = vec3(p->ax[i], p->ay[i], p->az[i]);
	cy.radius = p->radii[i];
	cy.height = p->heights[i];
	cy.mat_idx = p->mat_ids[i];
	return (cy);
}

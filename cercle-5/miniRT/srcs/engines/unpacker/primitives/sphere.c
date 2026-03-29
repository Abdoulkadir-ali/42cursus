/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_sphere	unpack_sphere(const t_primitive_array *p, int i)
{
	t_sphere	s;

	ft_memset(&s, 0, sizeof(s));
	if (i < 0 || (size_t)i >= p->count)
		return (s);
	s.center = vec3(p->px[i], p->py[i], p->pz[i]);
	s.radius = p->radii[i];
	s.mat_idx = p->mat_ids[i];
	return (s);
}

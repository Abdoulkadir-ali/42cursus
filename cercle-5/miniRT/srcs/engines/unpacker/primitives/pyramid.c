/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unpacker.h"

t_pyramid	unpack_pyramid(const t_primitive_array *p, int i)
{
	t_pyramid	py;

	ft_memset(&py, 0, sizeof(py));
	if (i < 0 || (size_t)i >= p->count)
		return (py);
	py.pos = vec3(p->px[i], p->py[i], p->pz[i]);
	py.up = vec3(p->ax[i], p->ay[i], p->az[i]);
	py.size = p->radii[i];
	py.height = p->heights[i];
	py.mat_idx = p->mat_ids[i];
	return (py);
}

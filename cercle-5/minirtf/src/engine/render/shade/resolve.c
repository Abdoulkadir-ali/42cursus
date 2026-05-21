/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:36:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

const t_object	*shade_resolve_obj(const t_scene *s, int idx)
{
	int	i;

	if (idx >= 0 && idx < (int)s->n_bvh)
		return (&s->bvh_objs[idx]);
	if (idx < 0)
	{
		i = -idx - 1;
		if (i >= 0 && i < (int)s->n_planes)
			return (&s->planes[i]);
	}
	return (NULL);
}

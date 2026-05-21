/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:53:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

t_object	*scene_obj_at(t_scene *s, int sel)
{
	size_t	i;

	if (sel >= 0 && (size_t)sel < s->n_bvh)
		return (&s->bvh_objs[sel]);
	if (sel < 0)
	{
		i = (size_t)(-sel - 1);
		if (i < s->n_planes)
			return (&s->planes[i]);
	}
	return (NULL);
}

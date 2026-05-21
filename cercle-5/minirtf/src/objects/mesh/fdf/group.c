/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "fdf.h"

void	fdf_group_objs(t_scene *s, int base, const char *path)
{
	int			gid;
	size_t		k;
	const char	*slash;
	const char	*nm;

	s->last_kind = 1;
	s->last_first = base;
	s->last_count = s->n_bvh - base;
	if (s->last_count > 0)
	{
		gid = s->next_group_id++;
		k = base;
		while (k < s->n_bvh)
			s->bvh_objs[k++].group_id = gid;
		if (gid < 64)
		{
			slash = strrchr(path, '/');
			nm = path;
			if (slash)
				nm = slash + 1;
			snprintf(s->group_names[gid], 64, "%s", nm);
		}
	}
}

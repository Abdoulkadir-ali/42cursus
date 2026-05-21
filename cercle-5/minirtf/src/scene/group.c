/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:53:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	scene_group_propagate(t_scene *s, int sel)
{
	const t_object	*src;
	int				gid;
	size_t			i;

	if (sel < 0 || (size_t)sel >= s->n_bvh)
		return ;
	src = &s->bvh_objs[sel];
	gid = src->group_id;
	if (gid <= 0)
		return ;
	i = 0;
	while (i < s->n_bvh)
	{
		if (i != (size_t)sel && s->bvh_objs[i].group_id == gid)
		{
			s->bvh_objs[i].mat = src->mat;
			s->bvh_objs[i].color = src->color;
		}
		i++;
	}
}

int	scene_group_delete(t_scene *s, int sel)
{
	int		gid;
	size_t	i;
	size_t	w;
	int		deleted;

	if (sel < 0 || (size_t)sel >= s->n_bvh)
		return (0);
	gid = s->bvh_objs[sel].group_id;
	if (gid <= 0)
	{
		memmove(&s->bvh_objs[sel], &s->bvh_objs[sel + 1],
			sizeof(t_object) * (s->n_bvh - (size_t)sel - 1));
		s->n_bvh--;
		return (1);
	}
	i = 0;
	w = 0;
	deleted = 0;
	while (i < s->n_bvh)
	{
		if (s->bvh_objs[i].group_id == gid)
			deleted++;
		else
			s->bvh_objs[w++] = s->bvh_objs[i];
		i++;
	}
	s->n_bvh = w;
	return (deleted);
}

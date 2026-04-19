/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbody.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static size_t	fill_bodies_b(t_scene *s, t_physics_body **lst, size_t n)
{
	size_t	i;

	i = 0;
	while (i < s->pyramid_count && n < MAX_NBODY)
		lst[n++] = &s->pyramids[i++].phys;
	i = 0;
	while (i < s->rect_count && n < MAX_NBODY)
		lst[n++] = &s->rects[i++].phys;
	i = 0;
	while (i < s->tri_count && n < MAX_NBODY)
		lst[n++] = &s->tris[i++].phys;
	return (n);
}

static size_t	fill_bodies_a(t_scene *s, t_physics_body **lst, size_t n)
{
	size_t	i;

	i = 0;
	while (i + s->proxy_sphere_count < s->sphere_count && n < MAX_NBODY)
		lst[n++] = &s->spheres[i++].phys;
	i = 0;
	while (i < s->box_count && n < MAX_NBODY)
		lst[n++] = &s->boxes[i++].phys;
	i = 0;
	while (i < s->capsule_count && n < MAX_NBODY)
		lst[n++] = &s->capsules[i++].phys;
	i = 0;
	while (i < s->cylinder_count && n < MAX_NBODY)
		lst[n++] = &s->cylinders[i++].phys;
	return (fill_bodies_b(s, lst, n));
}

void	apply_nbody_gravity(t_scene *scene, double big_g)
{
	static t_physics_body	*lst[MAX_NBODY];
	size_t					n;
	size_t					i;
	size_t					j;

	if (!scene || big_g < 1e-30)
		return ;
	n = fill_bodies_a(scene, lst, 0);
	i = 0;
	while (i < n)
	{
		j = i + 1;
		while (j < n)
		{
			apply_pair_grav(lst[i], lst[j], big_g);
			apply_pair_mag(lst[i], lst[j]);
			j++;
		}
		i++;
	}
}

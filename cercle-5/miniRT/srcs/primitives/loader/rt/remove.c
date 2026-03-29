/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 16:17:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	free_shift_prim_meta(t_scene *scene, size_t idx)
{
	size_t	rem;

	if (!scene->prim_meta)
		return ;
	free(scene->prim_meta[idx].file_path);
	free(scene->prim_meta[idx].user_comment);
	rem = scene->primitives.count - idx - 1;
	ft_memmove(scene->prim_meta + idx, scene->prim_meta + idx + 1,
		rem * sizeof(t_primitive_metadata));
}

static void	shift_prim_floats(t_primitive_array *p, size_t i)
{
	size_t	nf;

	nf = (p->count - i - 1) * sizeof(float);
	ft_memmove(p->px + i, p->px + i + 1, nf);
	ft_memmove(p->py + i, p->py + i + 1, nf);
	ft_memmove(p->pz + i, p->pz + i + 1, nf);
	ft_memmove(p->ax + i, p->ax + i + 1, nf);
	ft_memmove(p->ay + i, p->ay + i + 1, nf);
	ft_memmove(p->az + i, p->az + i + 1, nf);
	ft_memmove(p->tx + i, p->tx + i + 1, nf);
	ft_memmove(p->ty + i, p->ty + i + 1, nf);
	ft_memmove(p->tz + i, p->tz + i + 1, nf);
	ft_memmove(p->radii + i, p->radii + i + 1, nf);
	ft_memmove(p->heights + i, p->heights + i + 1, nf);
	ft_memmove(p->ex + i, p->ex + i + 1, nf);
}

static void	shift_prim_extra(t_primitive_array *p, size_t i)
{
	size_t	nf;
	size_t	nb;

	nf = (p->count - i - 1) * sizeof(float);
	nb = (p->count - i - 1);
	ft_memmove(p->ey + i, p->ey + i + 1, nf);
	ft_memmove(p->ez + i, p->ez + i + 1, nf);
	ft_memmove(p->abb_min_x + i, p->abb_min_x + i + 1, nf);
	ft_memmove(p->abb_min_y + i, p->abb_min_y + i + 1, nf);
	ft_memmove(p->abb_min_z + i, p->abb_min_z + i + 1, nf);
	ft_memmove(p->abb_max_x + i, p->abb_max_x + i + 1, nf);
	ft_memmove(p->abb_max_y + i, p->abb_max_y + i + 1, nf);
	ft_memmove(p->abb_max_z + i, p->abb_max_z + i + 1, nf);
	ft_memmove(p->types + i, p->types + i + 1, nb * sizeof(uint8_t));
	ft_memmove(p->mat_ids + i, p->mat_ids + i + 1, nb * sizeof(uint16_t));
	ft_memmove(p->is_static + i, p->is_static + i + 1, nb * sizeof(uint8_t));
	ft_memmove(p->has_phys + i, p->has_phys + i + 1, nb * sizeof(uint8_t));
	ft_memmove(p->phys_idx + i, p->phys_idx + i + 1, nb * sizeof(int));
}

bool	scene_remove_primitive(t_scene *scene, size_t idx)
{
	if (!scene || idx >= scene->primitives.count)
		return (false);
	free_shift_prim_meta(scene, idx);
	shift_prim_floats(&scene->primitives, idx);
	shift_prim_extra(&scene->primitives, idx);
	scene->primitives.count--;
	return (true);
}

static void	shift_tri_verts(t_tri_array *t, size_t i)
{
	size_t	nf;

	nf = (t->count - i - 1) * sizeof(float);
	ft_memmove(t->vx[0] + i, t->vx[0] + i + 1, nf);
	ft_memmove(t->vx[1] + i, t->vx[1] + i + 1, nf);
	ft_memmove(t->vx[2] + i, t->vx[2] + i + 1, nf);
	ft_memmove(t->vy[0] + i, t->vy[0] + i + 1, nf);
	ft_memmove(t->vy[1] + i, t->vy[1] + i + 1, nf);
	ft_memmove(t->vy[2] + i, t->vy[2] + i + 1, nf);
	ft_memmove(t->vz[0] + i, t->vz[0] + i + 1, nf);
	ft_memmove(t->vz[1] + i, t->vz[1] + i + 1, nf);
	ft_memmove(t->vz[2] + i, t->vz[2] + i + 1, nf);
	ft_memmove(t->ex[0] + i, t->ex[0] + i + 1, nf);
	ft_memmove(t->ex[1] + i, t->ex[1] + i + 1, nf);
	ft_memmove(t->ey[0] + i, t->ey[0] + i + 1, nf);
}

bool	scene_remove_tri(t_scene *scene, size_t idx)
{
	t_tri_array	*t;
	size_t		nf;
	size_t		nb;

	if (!scene || idx >= scene->tri_soa.count)
		return (false);
	t = &scene->tri_soa;
	nf = (t->count - idx - 1) * sizeof(float);
	nb = (t->count - idx - 1) * sizeof(uint16_t);
	shift_tri_verts(t, idx);
	ft_memmove(t->ey[1] + idx, t->ey[1] + idx + 1, nf);
	ft_memmove(t->ez[0] + idx, t->ez[0] + idx + 1, nf);
	ft_memmove(t->ez[1] + idx, t->ez[1] + idx + 1, nf);
	ft_memmove(t->nx + idx, t->nx + idx + 1, nf);
	ft_memmove(t->ny + idx, t->ny + idx + 1, nf);
	ft_memmove(t->nz + idx, t->nz + idx + 1, nf);
	ft_memmove(t->tx + idx, t->tx + idx + 1, nf);
	ft_memmove(t->ty + idx, t->ty + idx + 1, nf);
	ft_memmove(t->tz + idx, t->tz + idx + 1, nf);
	ft_memmove(t->mat_ids + idx, t->mat_ids + idx + 1, nb);
	t->count--;
	return (true);
}

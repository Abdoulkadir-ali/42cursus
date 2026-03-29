/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snapshot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 18:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 14:47:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	*dup_buf(const void *src, size_t n, size_t elem)
{
	void	*dst;

	if (!src || n == 0)
		return (NULL);
	dst = malloc(n * elem);
	if (dst)
		ft_memcpy(dst, src, n * elem);
	return (dst);
}

static void	snap_prim_soa(t_primitive_array *d, const t_primitive_array *s)
{
	size_t	n;

	n = s->count;
	*d = *s;
	d->types = dup_buf(s->types, n, sizeof(uint8_t));
	d->px = dup_buf(s->px, n, sizeof(float));
	d->py = dup_buf(s->py, n, sizeof(float));
	d->pz = dup_buf(s->pz, n, sizeof(float));
	d->ax = dup_buf(s->ax, n, sizeof(float));
	d->ay = dup_buf(s->ay, n, sizeof(float));
	d->az = dup_buf(s->az, n, sizeof(float));
	d->tx = dup_buf(s->tx, n, sizeof(float));
	d->ty = dup_buf(s->ty, n, sizeof(float));
	d->tz = dup_buf(s->tz, n, sizeof(float));
	d->radii = dup_buf(s->radii, n, sizeof(float));
	d->heights = dup_buf(s->heights, n, sizeof(float));
	d->ex = dup_buf(s->ex, n, sizeof(float));
	d->ey = dup_buf(s->ey, n, sizeof(float));
	d->ez = dup_buf(s->ez, n, sizeof(float));
	d->mat_ids = dup_buf(s->mat_ids, n, sizeof(uint16_t));
	d->is_static = dup_buf(s->is_static, n, sizeof(uint8_t));
	d->has_phys = dup_buf(s->has_phys, n, sizeof(uint8_t));
	d->abb_min_x = dup_buf(s->abb_min_x, n, sizeof(float));
	d->abb_min_y = dup_buf(s->abb_min_y, n, sizeof(float));
	d->abb_min_z = dup_buf(s->abb_min_z, n, sizeof(float));
	d->abb_max_x = dup_buf(s->abb_max_x, n, sizeof(float));
	d->abb_max_y = dup_buf(s->abb_max_y, n, sizeof(float));
	d->abb_max_z = dup_buf(s->abb_max_z, n, sizeof(float));
	d->phys_idx = dup_buf(s->phys_idx, n, sizeof(int));
}

static void	snap_tri_soa(t_tri_array *d, const t_tri_array *s)
{
	size_t	n;
	int		i;

	n = s->count;
	*d = *s;
	i = 0;
	while (i < 3)
	{
		d->vx[i] = dup_buf(s->vx[i], n, sizeof(float));
		d->vy[i] = dup_buf(s->vy[i], n, sizeof(float));
		d->vz[i] = dup_buf(s->vz[i], n, sizeof(float));
		i++;
	}
	i = 0;
	while (i < 2)
	{
		d->ex[i] = dup_buf(s->ex[i], n, sizeof(float));
		d->ey[i] = dup_buf(s->ey[i], n, sizeof(float));
		d->ez[i] = dup_buf(s->ez[i], n, sizeof(float));
		i++;
	}
	d->nx = dup_buf(s->nx, n, sizeof(float));
	d->ny = dup_buf(s->ny, n, sizeof(float));
	d->nz = dup_buf(s->nz, n, sizeof(float));
	d->tx = dup_buf(s->tx, n, sizeof(float));
	d->ty = dup_buf(s->ty, n, sizeof(float));
	d->tz = dup_buf(s->tz, n, sizeof(float));
	d->mat_ids = dup_buf(s->mat_ids, n, sizeof(uint16_t));
}

void	scene_snapshot(t_scene_snap *snap, t_gui *gui)
{
	t_scene		*sc;

	sc = gui->scene;
	ft_memset(snap, 0, sizeof(*snap));
	snap_prim_soa(&snap->prims, &sc->primitives);
	snap_tri_soa(&snap->tris, &sc->tri_soa);
	snap->lights = dup_buf(sc->lights, sc->light_count, sizeof(t_light));
	snap->light_count = sc->light_count;
	snap->materials = dup_buf(sc->materials, sc->mat_count, sizeof(t_material));
	snap->mat_count = sc->mat_count;
	snap->ambient = sc->ambient;
	snap->camera = sc->camera;
}

void	scene_snap_free(t_scene_snap *snap)
{
	t_primitive_array	*p;
	t_tri_array			*t;
	int					i;

	if (!snap)
		return ;
	p = &snap->prims;
	free(p->types); free(p->px); free(p->py); free(p->pz);
	free(p->ax); free(p->ay); free(p->az);
	free(p->tx); free(p->ty); free(p->tz);
	free(p->radii); free(p->heights);
	free(p->ex); free(p->ey); free(p->ez);
	free(p->mat_ids); free(p->is_static); free(p->has_phys);
	free(p->abb_min_x); free(p->abb_min_y); free(p->abb_min_z);
	free(p->abb_max_x); free(p->abb_max_y); free(p->abb_max_z);
	free(p->phys_idx);
	t = &snap->tris;
	i = 0;
	while (i < 3)
	{
		free(t->vx[i]); free(t->vy[i]); free(t->vz[i]);
		i++;
	}
	i = 0;
	while (i < 2)
	{
		free(t->ex[i]); free(t->ey[i]); free(t->ez[i]);
		i++;
	}
	free(t->nx); free(t->ny); free(t->nz);
	free(t->tx); free(t->ty); free(t->tz);
	free(t->mat_ids);
	free(snap->lights);
	free(snap->materials);
	ft_memset(snap, 0, sizeof(*snap));
}

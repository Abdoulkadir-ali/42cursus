/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 17:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:16:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "core.h"

#define MAX_GRID_CELLS 4194304

static int	ensure_int_buf(int **buf, int *cap, int need)
{
	int	*tmp;

	if (need <= *cap)
		return (0);
	tmp = (int *)realloc(*buf, sizeof(int) * need);
	if (!tmp)
		return (-1);
	*buf = tmp;
	*cap = need;
	return (0);
}

static inline int cell_index(const t_phys_world *w, const t_vec3 p)
{
	int	ix;
	int	iy;
	int	iz;

	ix = (int)((p.x - w->bmin.x) / w->cell_size);
	iy = (int)((p.y - w->bmin.y) / w->cell_size);
	iz = (int)((p.z - w->bmin.z) / w->cell_size);
	if (ix < 0)
		ix = 0;
	if (iy < 0)
		iy = 0;
	if (iz < 0)
		iz = 0;
	if (ix >= w->nx)
		ix = w->nx - 1;
	if (iy >= w->ny)
		iy = w->ny - 1;
	if (iz >= w->nz)
		iz = w->nz - 1;
	return ((iz * w->ny + iy) * w->nx + ix);
}

int	build_grid(t_phys_world *w)
{
	t_vec3	bmax;
	float	r;
	int	i;
	int	cells;

	if (w->n == 0)
		return (-1);
	w->bmin = w->bodies[0].pos;
	bmax = w->bmin;
	r = w->bodies[0].radius_cache;
	i = 1;
	while (i < w->n)
	{
		if (w->bodies[i].pos.x < w->bmin.x)
			w->bmin.x = w->bodies[i].pos.x;
		if (w->bodies[i].pos.y < w->bmin.y)
			w->bmin.y = w->bodies[i].pos.y;
		if (w->bodies[i].pos.z < w->bmin.z)
			w->bmin.z = w->bodies[i].pos.z;
		if (w->bodies[i].pos.x > bmax.x)
			bmax.x = w->bodies[i].pos.x;
		if (w->bodies[i].pos.y > bmax.y)
			bmax.y = w->bodies[i].pos.y;
		if (w->bodies[i].pos.z > bmax.z)
			bmax.z = w->bodies[i].pos.z;
		if (w->bodies[i].radius_cache > r)
			r = w->bodies[i].radius_cache;
		i++;
	}
	w->cell_size = r * 2.05f;
	if (w->cell_size < 1e-3f)
		w->cell_size = 1e-3f;
	w->nx = (int)((bmax.x - w->bmin.x) / w->cell_size) + 1;
	w->ny = (int)((bmax.y - w->bmin.y) / w->cell_size) + 1;
	w->nz = (int)((bmax.z - w->bmin.z) / w->cell_size) + 1;
	if (w->nx < 1)
		w->nx = 1;
	if (w->ny < 1)
		w->ny = 1;
	if (w->nz < 1)
		w->nz = 1;
	while ((double)w->nx * w->ny * w->nz > MAX_GRID_CELLS)
	{
		w->cell_size *= 2.0f;
		w->nx = (w->nx + 1) / 2;
		w->ny = (w->ny + 1) / 2;
		w->nz = (w->nz + 1) / 2;
	}
	cells = w->nx * w->ny * w->nz;
	if (cells + 1 > w->cells_cap)
	{
		if (ensure_int_buf(&w->cell_count, &w->cells_cap, cells + 1) < 0)
			return (-1);
		w->cells_cap = cells + 1;
		free(w->cell_start);
		w->cell_start = (int *)malloc(sizeof(int) * w->cells_cap);
		if (!w->cell_start)
			return (-1);
	}
	if (ensure_int_buf(&w->cell_items, &w->items_cap, w->n) < 0)
		return (-1);
	memset(w->cell_count, 0, sizeof(int) * (cells + 1));
	return (cells);
}

int	bin_bodies(t_phys_world *w, int cells)
{
	int	i;
	int	c;
	int	acc;
	int	*fill;

	fill = (int *)malloc(sizeof(int) * (cells + 1));
	if (!fill)
	{
		fprintf(stderr, "bin_bodies: allocation failed for %d cells\n", cells + 1);
		return (-1);
	}
	i = 0;
	while (i < w->n)
	{
		c = cell_index(w, w->bodies[i].pos);
		w->cell_count[c]++;
		i++;
	}
	acc = 0;
	i = 0;
	while (i <= cells)
	{
		w->cell_start[i] = acc;
		fill[i] = acc;
		acc += w->cell_count[i];
		i++;
	}
	i = 0;
	while (i < w->n)
	{
		c = cell_index(w, w->bodies[i].pos);
		w->cell_items[fill[c]++] = i;
		i++;
	}
	free(fill);
	return (0);
}

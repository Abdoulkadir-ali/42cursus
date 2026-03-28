/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 07:22:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* ------------------------------------------------------------------ */
/* Staging buffer lifecycle                                            */
/* ------------------------------------------------------------------ */

bool	rt_buf_init(t_rt_buf *buf)
{
	ft_memset(buf, 0, sizeof(t_rt_buf));
	buf->shapes = malloc(64 * sizeof(t_rt_shape));
	buf->lights = malloc(16 * sizeof(t_light));
	if (!buf->shapes || !buf->lights)
	{
		free(buf->shapes);
		free(buf->lights);
		return (false);
	}
	buf->shape_cap = 64;
	buf->light_cap = 16;
	return (true);
}

void	rt_buf_free(t_rt_buf *buf)
{
	free(buf->shapes);
	free(buf->lights);
	ft_memset(buf, 0, sizeof(t_rt_buf));
}

/*
** Inject all validated transients from buf into scene.
** Called only after the ENTIRE .rt file has been parsed successfully.
*/
bool	rt_buf_inject(t_scene *scene, t_rt_buf *buf)
{
	size_t		i;
	t_rt_shape	*s;

	if (buf->has_ambient)
		scene_apply_ambient(scene, buf->ambient.brightness, buf->ambient.rgb);
	if (buf->has_camera)
		scene_apply_camera(scene, buf->camera.transform, buf->camera.fov);
	i = 0;
	while (i < buf->light_count)
	{
		if (!scene_add_light(scene, buf->lights[i]))
			return (false);
		i++;
	}
	i = 0;
	while (i < buf->shape_count)
	{
		s = &buf->shapes[i];
		if (s->type == PRIM_TRIANGLE)
		{
			s->params.mat_id = scene_add_material_from_color(scene, s->color);
			if (!scene_add_tri(scene, s->v, s->params.mat_id))
				return (false);
		}
		else
		{
			s->params.mat_id = scene_add_material_from_color(scene, s->color);
			if (!scene_add_primitive(scene, s->params, s->type))
				return (false);
		}
		i++;
	}
	return (true);
}

static bool	realloc_prim_soa(t_primitive_array *arr, size_t new_cap)
{
	uint8_t		*nty, *ns, *hp;
	float		*npx, *nax, *ntx, *nr, *nh, *nex, *nmix, *nmax;
	uint16_t	*nm;
	int			*nph;

	nty = realloc(arr->types, new_cap);
	npx = realloc(arr->px, new_cap * 4 * 3); /* px, py, pz */
	nax = realloc(arr->ax, new_cap * 4 * 3); /* ax, ay, az */
	ntx = realloc(arr->tx, new_cap * 4 * 3); /* tx, ty, tz */
	nr = realloc(arr->radii, new_cap * 4);
	nh = realloc(arr->heights, new_cap * 4);
	nex = realloc(arr->ex, new_cap * 4 * 3); /* ex, ey, ez */
	nm = realloc(arr->mat_ids, new_cap * 2);
	ns = realloc(arr->is_static, new_cap);
	hp = realloc(arr->has_phys, new_cap);
	nmix = realloc(arr->abb_min_x, new_cap * 4 * 3);
	nmax = realloc(arr->abb_max_x, new_cap * 4 * 3);
	nph = realloc(arr->phys_idx, new_cap * 4);
	if (!nty || !npx || !nax || !ntx || !nr || !nh || !nex || !nm || !ns || !hp || !nmix || !nmax || !nph)
		return (false);
	arr->types = nty;
	arr->px = npx; arr->py = npx + new_cap; arr->pz = npx + 2 * new_cap;
	arr->ax = nax; arr->ay = nax + new_cap; arr->az = nax + 2 * new_cap;
	arr->tx = ntx; arr->ty = ntx + new_cap; arr->tz = ntx + 2 * new_cap;
	arr->radii = nr; arr->heights = nh;
	arr->ex = nex; arr->ey = nex + new_cap; arr->ez = nex + 2 * new_cap;
	arr->mat_ids = nm; arr->is_static = ns; arr->has_phys = hp;
	arr->abb_min_x = nmix; arr->abb_min_y = nmix + new_cap; arr->abb_min_z = nmix + 2 * new_cap;
	arr->abb_max_x = nmax; arr->abb_max_y = nmax + new_cap; arr->abb_max_z = nmax + 2 * new_cap;
	arr->phys_idx = nph; arr->capacity = new_cap;
	return (true);
}

bool	scene_add_primitive(t_scene *scene, t_prim_params params, t_prim_type type)
{
	size_t	idx;

	if (scene->primitives.count >= scene->primitives.capacity)
		if (!realloc_prim_soa(&scene->primitives, (scene->primitives.capacity == 0) ? 1024 : scene->primitives.capacity * 2))
			return (false);
	idx = scene->primitives.count++;
	scene->primitives.types[idx] = (uint8_t)type;
	scene->primitives.px[idx] = (float)params.pos.x;
	scene->primitives.py[idx] = (float)params.pos.y;
	scene->primitives.pz[idx] = (float)params.pos.z;
	scene->primitives.ax[idx] = (float)params.axis.x;
	scene->primitives.ay[idx] = (float)params.axis.y;
	scene->primitives.az[idx] = (float)params.axis.z;
	scene->primitives.tx[idx] = (float)params.tangent.x;
	scene->primitives.ty[idx] = (float)params.tangent.y;
	scene->primitives.tz[idx] = (float)params.tangent.z;
	scene->primitives.ex[idx] = (float)params.extents.x;
	scene->primitives.ey[idx] = (float)params.extents.y;
	scene->primitives.ez[idx] = (float)params.extents.z;
	scene->primitives.radii[idx] = (float)params.radius;
	scene->primitives.heights[idx] = (float)params.height;
	scene->primitives.mat_ids[idx] = (uint16_t)params.mat_id;
	scene->primitives.phys_idx[idx] = -1;
	scene->primitives.is_static[idx] = 1;
	scene->primitives.has_phys[idx] = 0;
	return (true);
}

static bool	realloc_tri_soa(t_tri_array *soa, size_t new_cap)
{
	int		k;
	size_t	sz = new_cap * sizeof(float);
	size_t	szm = new_cap * sizeof(uint16_t);

	k = -1;
	while (++k < 3)
	{
		soa->vx[k] = realloc(soa->vx[k], sz); soa->vy[k] = realloc(soa->vy[k], sz); soa->vz[k] = realloc(soa->vz[k], sz);
	}
	soa->nx = realloc(soa->nx, sz); soa->ny = realloc(soa->ny, sz); soa->nz = realloc(soa->nz, sz);
	soa->tx = realloc(soa->tx, sz); soa->ty = realloc(soa->ty, sz); soa->tz = realloc(soa->tz, sz);
	soa->mat_ids = realloc(soa->mat_ids, szm);
	soa->cap = new_cap;
	return (soa->nx != NULL && soa->tx != NULL && soa->mat_ids != NULL);
}

bool	scene_add_tri(t_scene *scene, t_vec3 v[3], int mat_id)
{
	size_t i; t_vec3 n;
	if (scene->tri_soa.count >= scene->tri_soa.cap)
		if (!realloc_tri_soa(&scene->tri_soa, (scene->tri_soa.cap == 0) ? 1024 : scene->tri_soa.cap * 2))
			return (false);
	i = scene->tri_soa.count++;
	scene->tri_soa.vx[0][i] = (float)v[0].x; scene->tri_soa.vy[0][i] = (float)v[0].y; scene->tri_soa.vz[0][i] = (float)v[0].z;
	scene->tri_soa.vx[1][i] = (float)v[1].x; scene->tri_soa.vy[1][i] = (float)v[1].y; scene->tri_soa.vz[1][i] = (float)v[1].z;
	scene->tri_soa.vx[2][i] = (float)v[2].x; scene->tri_soa.vy[2][i] = (float)v[2].y; scene->tri_soa.vz[2][i] = (float)v[2].z;
	n = vec3_norm(vec3_cross(vec3_sub(v[1], v[0]), vec3_sub(v[2], v[0])));
	scene->tri_soa.nx[i] = (float)n.x; scene->tri_soa.ny[i] = (float)n.y; scene->tri_soa.nz[i] = (float)n.z;
	scene->tri_soa.mat_ids[i] = (uint16_t)mat_id;
	return (true);
}

void	scene_apply_camera(t_scene *scene, t_transform transform, double fov)
{
	scene->camera.transform = transform;
	scene->camera.fov = fov;
}

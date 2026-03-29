/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   injection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 06:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 17:55:33 by abdoali          ###   ########.fr       */
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
	time_t		t;

	t = time(NULL);
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
		s->params.mat_id = scene_add_material_from_color(scene, s->color);
		if (s->type == PRIM_TRIANGLE)
		{
			if (!scene_add_tri(scene, s->data.tri, s->params.mat_id))
				return (false);
		}
		else if (!scene_add_primitive_with_time(scene, s->params, s->type, t))
			return (false);
		i++;
	}
	return (true);
}

static bool	realloc_soa_slabs(t_primitive_array *arr, size_t nc)
{
	float	*f;

	f = realloc(arr->float_slab, nc * 20 * sizeof(float));
	if (!f)
		return (false);
	arr->float_slab = f;
	arr->px = f + 0 * nc; arr->py = f + 1 * nc; arr->pz = f + 2 * nc;
	arr->ax = f + 3 * nc; arr->ay = f + 4 * nc; arr->az = f + 5 * nc;
	arr->tx = f + 6 * nc; arr->ty = f + 7 * nc; arr->tz = f + 8 * nc;
	arr->radii = f + 9 * nc; arr->heights = f + 10 * nc;
	arr->ex = f + 11 * nc; arr->ey = f + 12 * nc; arr->ez = f + 13 * nc;
	arr->abb_min_x = f + 14 * nc; arr->abb_min_y = f + 15 * nc; arr->abb_min_z = f + 16 * nc;
	arr->abb_max_x = f + 17 * nc; arr->abb_max_y = f + 18 * nc; arr->abb_max_z = f + 19 * nc;
	return (true);
}

static bool	realloc_meta_a(t_primitive_array *arr, size_t nc)
{
	uint8_t		*ty;
	uint16_t	*mid;
	uint8_t		*st;
	uint8_t		*hp;

	ty = realloc(arr->types, nc);
	mid = realloc(arr->mat_ids, nc * sizeof(uint16_t));
	st = realloc(arr->is_static, nc);
	hp = realloc(arr->has_phys, nc);
	if (!ty || !mid || !st || !hp)
		return (false);
	arr->types = ty;
	arr->mat_ids = mid;
	arr->is_static = st;
	arr->has_phys = hp;
	return (true);
}

static bool	realloc_meta_b(t_scene *s, t_primitive_array *arr, size_t nc)
{
	int					*ph;
	t_primitive_metadata	*pm;

	ph = realloc(arr->phys_idx, nc * sizeof(int));
	pm = realloc(s->prim_meta, nc * sizeof(t_primitive_metadata));
	if (!ph || !pm)
		return (false);
	arr->phys_idx = ph;
	s->prim_meta = pm;
	return (true);
}

static bool	realloc_prim_soa(t_scene *s, t_primitive_array *arr, size_t new_cap)
{
	if (!realloc_soa_slabs(arr, new_cap))
		return (false);
	if (!realloc_meta_a(arr, new_cap))
		return (false);
	if (!realloc_meta_b(s, arr, new_cap))
		return (false);
	arr->capacity = new_cap;
	return (true);
}

static bool	add_prim_meta(t_scene *s, size_t idx, time_t t)
{
	t_primitive_metadata	*m;

	if (!s->prim_meta)
		return (false);
	m = &s->prim_meta[idx];
	ft_memset(m, 0, sizeof(t_primitive_metadata));
	m->orig_px = s->primitives.px[idx];
	m->orig_py = s->primitives.py[idx];
	m->orig_pz = s->primitives.pz[idx];
	m->orig_ax = s->primitives.ax[idx];
	m->orig_ay = s->primitives.ay[idx];
	m->orig_az = s->primitives.az[idx];
	m->orig_radii = s->primitives.radii[idx];
	m->orig_heights = s->primitives.heights[idx];
	m->import_time = t;
	return (true);
}

bool	scene_add_primitive_with_time(t_scene *scene, t_prim_params params, 
		t_prim_type type, time_t t)
{
	size_t	idx;

	if (scene->primitives.count >= scene->primitives.capacity)
		if (!realloc_prim_soa(scene, &scene->primitives, 
				(scene->primitives.capacity == 0) ? 1024 : scene->primitives.capacity * 2))
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
	if (!add_prim_meta(scene, idx, t))
	{
		scene->primitives.count--;
		return (false);
	}
	if (type == PRIM_PLANE)
	{
		if (scene->plane_count >= scene->plane_cap)
		{
			int *tmp = realloc(scene->plane_indices, (scene->plane_cap + 16) * sizeof(int));
			if (!tmp) return (true);
			scene->plane_indices = tmp;
			scene->plane_cap += 16;
		}
		scene->plane_indices[scene->plane_count++] = (int)idx;
	}
	return (true);
}

bool	scene_add_primitive(t_scene *scene, t_prim_params params, t_prim_type type)
{
	return (scene_add_primitive_with_time(scene, params, type, time(NULL)));
}

static bool	realloc_tri_soa(t_tri_array *soa, size_t new_cap)
{
	float		*f;
	uint16_t	*nm;

	f = realloc(soa->float_slab, new_cap * 21 * sizeof(float));
	nm = realloc(soa->mat_ids, new_cap * sizeof(uint16_t));
	if (!f || !nm)
		return (false);
	soa->float_slab = f;
	soa->vx[0] = f + 0 * new_cap; soa->vy[0] = f + 1 * new_cap; soa->vz[0] = f + 2 * new_cap;
	soa->vx[1] = f + 3 * new_cap; soa->vy[1] = f + 4 * new_cap; soa->vz[1] = f + 5 * new_cap;
	soa->vx[2] = f + 6 * new_cap; soa->vy[2] = f + 7 * new_cap; soa->vz[2] = f + 8 * new_cap;
	soa->ex[0] = f + 9 * new_cap; soa->ey[0] = f + 10 * new_cap; soa->ez[0] = f + 11 * new_cap;
	soa->ex[1] = f + 12 * new_cap; soa->ey[1] = f + 13 * new_cap; soa->ez[1] = f + 14 * new_cap;
	soa->nx = f + 15 * new_cap; soa->ny = f + 16 * new_cap; soa->nz = f + 17 * new_cap;
	soa->tx = f + 18 * new_cap; soa->ty = f + 19 * new_cap; soa->tz = f + 20 * new_cap;
	soa->mat_ids = nm;
	soa->cap = new_cap;
	return (true);
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


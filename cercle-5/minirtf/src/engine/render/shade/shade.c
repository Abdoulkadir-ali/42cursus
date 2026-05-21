/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "core.h"

static t_vec3	cosine_sample_hemisphere(t_vec3 n, int seed);

static void	shade_material_uv(const t_object *o, const t_hit *h,
				 float *u, float *v)
{
	if (o->type == OBJ_TRIANGLE)
	{
		float	b0;

		b0 = 1.0f - h->u - h->v;
		const float *uv = o->u.tri.uv;
		*u = b0 * uv[0] + h->u * uv[2] + h->v * uv[4];
		*v = b0 * uv[1] + h->u * uv[3] + h->v * uv[5];
	}
	else
		object_uv(o, h->p, u, v);
}

static t_vec3	shade_emission(const t_app *app, const t_object *o,
				 const t_hit *h, t_vec3 col, float u, float v)
{
	t_vec3	ec;

	if (app->set.rt.blackbody)
		col = v3_add(col, emissive_color(&o->mat));
	if (o->mat.emit_power > 0.0f)
	{
		ec = v3_mul(o->mat.emit_color, o->mat.emit_power);
		if (o->mat.emit_tex_id >= 0 && (size_t)o->mat.emit_tex_id < app->scene.n_textures)
		{
			float	dist;
			float	lod;
			t_vec3	tc;

			dist = v3_len(v3_sub(h->p, app->scene.cam.pos));
			lod = app->set.anim.use_mips ? log2f(fmaxf(1.0f, dist * 0.05f)) + app->set.anim.mip_bias : 0.0f;
			tc = texture_sample(&app->scene.textures[o->mat.emit_tex_id], u, v, lod);
			ec = v3_hmul(ec, tc);
		}
		col = v3_add(col, ec);
	}
	return (col);
}

static t_vec3	shade_indirect(const t_app *app, const t_hit *h,
				 const t_vec3 albedo, int depth)
{
	t_vec3	col;
	t_ray	ir;

	col = v3(0, 0, 0);
	if (app->set.rt.indirect_light && depth == 0)
	{
		ir.d = cosine_sample_hemisphere(h->n, app->accum_samples + h->obj_index);
		ir.o = v3_add(h->p, v3_mul(h->n, EPSILON * 4.0f));
		col = trace_ray(app, &ir, depth + 1);
		col = v3_hmul(albedo, col);
	}
	return (col);
}

static t_vec3	cosine_sample_hemisphere(t_vec3 n, int seed)
{
	float	r1;
	float	r2;
	float	phi;
	float	radius;
	t_vec3	u;
	t_vec3	v;
	t_vec3	local;

	r1 = halton(seed, 2);
	r2 = halton(seed, 3);
	phi = 2.0f * (float)M_PI * r1;
	radius = sqrtf(r2);
	local = v3(radius * cosf(phi), radius * sinf(phi), sqrtf(fmaxf(0.0f, 1.0f - r2)));
	basis_from_axis(n, &u, &v);
	return (v3_add(v3_mul(u, local.x), v3_add(v3_mul(v, local.y), v3_mul(n, local.z))));
}

static t_vec3	shade_reflection(const t_app *app, const t_ray *r,
				 const t_hit *h, const t_vec3 albedo,
				 float refl_w)
{
	t_ray	rr;
	t_vec3	rcol;
	t_vec3	tint;
	t_vec3	tinted;

	rr.d = v3_norm(v3_sub(r->d, v3_mul(h->n, 2.0f * v3_dot(r->d, h->n))));
	rr.o = v3_add(h->p, v3_mul(h->n, EPSILON * 4.0f));
	rcol = trace_ray(app, &rr, 1);
	tint = v3_add(v3_mul(albedo, h->mat->metallic), v3_mul(v3(1, 1, 1), 1.0f - h->mat->metallic));
	tinted = v3_hmul(rcol, tint);
	return (v3_add(v3_mul(tinted, refl_w), v3_mul(v3(1, 1, 1), 1.0f - refl_w)));
}

static t_vec3	shade_transparency(const t_app *app, const t_ray *r,
				 const t_hit *h, const t_vec3 col, float refl_w)
{
	t_ray	tr;
	t_vec3	rcol;
	float	w;

	tr.d = r->d;
	tr.o = v3_add(h->p, v3_mul(r->d, EPSILON * 8.0f));
	rcol = trace_ray(app, &tr, 1);
	w = (1.0f - h->mat->opacity) * (1.0f - refl_w);
	return (v3_add(v3_mul(col, 1.0f - w), v3_mul(rcol, w)));
}


t_vec3	shade(const t_app *app, const t_ray *r, const t_hit *h, int depth)
{
	const t_scene	*s;
	const t_object	*o;
	t_vec3		albedo;
	t_vec3		col;
	t_vec3		view;
	float		u;
	float		v;
	float		cos_t;
	float		refl_w;

	s = &app->scene;
	o = shade_resolve_obj(s, h->obj_index);
	if (!o)
		return (v3(0, 0, 0));
	((t_hit *)h)->mat = &o->mat;
	shade_material_uv(o, h, &u, &v);
	albedo = material_albedo(app, &o->mat, u, v, v3_len(v3_sub(h->p, app->scene.cam.pos)));
	view = v3_neg(r->d);
	col = v3_hmul(albedo, v3_mul(s->amb.color, s->amb.ratio));
	for (size_t i = 0; i < s->n_lights; i++)
		col = v3_add(col, phong_light(app, h, albedo, &s->lights[i], view));
	col = shade_emission(app, o, h, col, u, v);
	col = v3_add(col, emitter_lights(app, h, albedo, view, depth));
	if (depth >= app->set.rt.max_bounces)
		return (col);
	col = v3_add(col, shade_indirect(app, h, albedo, depth));
	cos_t = fmaxf(0.0f, v3_dot(view, h->n));
	refl_w = o->mat.reflectivity;
	if (o->mat.metallic > 0.001f)
		refl_w = fmaxf(refl_w, o->mat.metallic);
	if (o->mat.opacity < 0.999f)
		refl_w = fmaxf(refl_w, fresnel(cos_t, o->mat.ior));
	if (refl_w > 0.001f)
		col = v3_add(v3_mul(col, 1.0f - refl_w), shade_reflection(app, r, h, albedo, refl_w));
	if (o->mat.opacity < 0.999f)
		col = shade_transparency(app, r, h, col, refl_w);
	return (col);
}

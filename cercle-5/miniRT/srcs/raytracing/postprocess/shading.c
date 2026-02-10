/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:00:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"


/*
** Checks if a point is in shadow for a given light source.
*/
static bool	is_in_shadow(t_scene *scene, const t_bvh *bvh, t_vec3 p, t_vec3 ldir)
{
	t_ray	shadow_ray;
	t_hit	sh_hit;
	int		i;
	double	dist;

	dist = vec3_mag(ldir);
	ray_init(&shadow_ray, p, vec3_norm(ldir));
	// ray_init handles inv_dir and sign now
	if (bvh_occluded(bvh, &shadow_ray, dist))
		return (true);
	i = 0;
	while (i < scene->plane_count)
	{
		ft_memset(&sh_hit, 0, sizeof(t_hit));
		if (intersect_plane(&shadow_ray, &scene->planes[i], &sh_hit))
		{
			if (sh_hit.t > EPSILON && sh_hit.t < dist)
				return (true);
		}
		i++;
	}
	return (false);
}

/*
** Scales and clamps a color value.
*/
static t_vec3	pixel_color(t_vec3 obj, t_vec3 light, double intensity)
{
	t_vec3	f;

	f.x = (obj.x / 255.0) * (light.x / 255.0) * intensity * 255.0;
	f.y = (obj.y / 255.0) * (light.y / 255.0) * intensity * 255.0;
	f.z = (obj.z / 255.0) * (light.z / 255.0) * intensity * 255.0;
	if (f.x > 255)
		f.x = 255;
	if (f.y > 255)
		f.y = 255;
	if (f.z > 255)
		f.z = 255;
	return (f);
}

/*
** Retrieves material for the hit object.
*/
static void	get_material(t_shading_ctx *ctx)
{
	t_hit	*h;

	h = ctx->hit;
	if (h->ref.type == TYPE_SPHERE)
		ctx->mat = ctx->scene->materials[ctx->scene->spheres[h->ref.index].mat_id];
	else if (h->ref.type == TYPE_PLANE)
		ctx->mat = ctx->scene->materials[ctx->scene->planes[h->ref.index].mat_id];
	else if (h->ref.type == TYPE_CYLINDER)
		ctx->mat = ctx->scene->materials[ctx->scene->cylinders[h->ref.index].mat_id];
	else if (h->ref.type == TYPE_CONE)
		ctx->mat = ctx->scene->materials[ctx->scene->cones[h->ref.index].mat_id];
	else if (h->ref.type == TYPE_MESH)
		ctx->mat = ctx->scene->materials[ctx->scene->meshes[h->ref.index].mat_id];
	else if (h->ref.type == TYPE_ANIM)
		ctx->mat = ctx->scene->materials[ctx->scene->animated[h->ref.index].base.mat_id];
	else
		ctx->mat = (t_material){0};
	if (h->ref.type == TYPE_MESH || h->ref.type == TYPE_ANIM)
	{
		static int dbg_cnt = 0;
		if (dbg_cnt++ < 5)
			printf("DEBUG SHADE: type=%d idx=%d mat_id=%d tex_type=%d "
				"colorA=(%.0f,%.0f,%.0f) normal=(%.2f,%.2f,%.2f)\n",
				h->ref.type, h->ref.index,
				ctx->scene->meshes[h->ref.index].mat_id,
				ctx->mat.albedo_map.type,
				ctx->mat.albedo_map.color_a.x,
				ctx->mat.albedo_map.color_a.y,
				ctx->mat.albedo_map.color_a.z,
				h->normal.x, h->normal.y, h->normal.z);
	}
}

/*
** Applies normal/bump mapping if available.
*/
static void	apply_bump(t_shading_ctx *ctx)
{
	t_vec3	s;
	t_vec3	m_n;
	t_vec3	n_n;

	if (ctx->mat.bump_map.type == TEX_SOLID || !ctx->mat.bump_map.img)
		return ;
	s = sample_texture(&ctx->mat.bump_map, ctx->hit->u, ctx->hit->v);
	m_n.x = (s.x / 255.0) * 2.0 - 1.0;
	m_n.y = (s.y / 255.0) * 2.0 - 1.0;
	m_n.z = (s.z / 255.0) * 2.0 - 1.0;
	n_n.x = ctx->hit->tangent.x * m_n.x + ctx->hit->bitangent.x * m_n.y
		+ ctx->hit->normal.x * m_n.z;
	n_n.y = ctx->hit->tangent.y * m_n.x + ctx->hit->bitangent.y * m_n.y
		+ ctx->hit->normal.y * m_n.z;
	n_n.z = ctx->hit->tangent.z * m_n.x + ctx->hit->bitangent.z * m_n.y
		+ ctx->hit->normal.z * m_n.z;
	ctx->hit->normal = vec3_norm(n_n);
}

/*
** Calculates lighting contribution for a single light source.
*/
static t_vec3	calc_light(t_shading_ctx *ctx, t_light light)
{
	t_vec3	ld;
	double	ndotl;
	t_vec3	half;
	double	spec;

	ld = vec3_sub(light.transform.pos, ctx->hit->point);
	ld = vec3_norm(ld);
	ndotl = vec3_dot(ctx->hit->normal, ld);
	if (ndotl <= 0.0)
		return (vec3(0, 0, 0));
	if (light.type == LIGHT_SPOT && vec3_dot(vec3_scale(ld, -1.0),
			light.transform.forward) < light.cutoff)
		return (vec3(0, 0, 0));
	if (is_in_shadow(ctx->scene, ctx->bvh, vec3_add(ctx->hit->point,
				vec3_scale(ctx->hit->normal, EPSILON)),
			vec3_sub(light.transform.pos, ctx->hit->point)))
		return (vec3(0, 0, 0));
	half = vec3_norm(vec3_add(ld, vec3_scale(ctx->ray->direction, -1.0)));
	spec = pow(fmax(0.0, vec3_dot(ctx->hit->normal, half)),
			ctx->mat.shininess);
	return (vec3_add(pixel_color(ctx->albedo, light.rgb, light.brightness
				* ndotl), vec3_scale(light.rgb, light.brightness
				* ctx->mat.specular * spec)));
}

/*
** Computes the final shaded color for a hit point.
*/
t_vec3	compute_color(t_hit *hit, t_scene *scene, const t_bvh *bvh,
		const t_ray *ray, int depth)
{
	t_shading_ctx	ctx;
	(void)depth;
	t_vec3			total;
	int				i;

	ctx.hit = hit;
	ctx.scene = scene;
	ctx.bvh = bvh;
	ctx.ray = ray;
	get_material(&ctx);
	ctx.albedo = sample_texture(&ctx.mat.albedo_map, hit->u, hit->v);
	apply_bump(&ctx);
	total = pixel_color(ctx.albedo, scene->ambient.rgb,
			scene->ambient.brightness);
	i = 0;
	while (i < scene->light_count)
	{
		total = vec3_add(total, calc_light(&ctx, scene->lights[i]));
		i++;
	}
	if (total.x > 255) total.x = 255;
	if (total.y > 255) total.y = 255;
	if (total.z > 255) total.z = 255;
	return (total);
}

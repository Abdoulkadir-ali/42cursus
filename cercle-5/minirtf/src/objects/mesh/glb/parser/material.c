/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 01:39:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"

static int	resolve_tex_image(t_glb *g, int tex_idx)
{
	const char	*tex;
	const char	*v;

	if (tex_idx < 0)
		return (-1);
	tex = json_arr_get(json_obj_find(g->json, g->jend, "textures"),
			g->jend, tex_idx);
	if (!tex)
		return (-1);
	v = json_obj_find(tex, g->jend, "source");
	if (!v)
		v = json_obj_find(tex, g->jend, "extensions");
	if (!v)
		return (-1);
	return ((int)json_int(v, g->jend));
}

static int	tex_index_in_block(const t_glb *g, const char *parent,
		const char *key)
{
	const char	*blk;
	const char	*v;

	if (!parent)
		return (-1);
	blk = json_obj_find(parent, g->jend, key);
	if (!blk)
		return (-1);
	v = json_obj_find(blk, g->jend, "index");
	if (!v)
		return (-1);
	return ((int)json_int(v, g->jend));
}

static t_vec3	read_vec3_factor(const t_glb *g, const char *parent,
		const char *key, t_vec3 def)
{
	const char	*v;
	t_vec3		o;

	o = def;
	if (!parent)
		return (o);
	v = json_obj_find(parent, g->jend, key);
	if (!v)
		return (o);
	o.x = (float)json_flt_idx(v, g->jend, 0);
	o.y = (float)json_flt_idx(v, g->jend, 1);
	o.z = (float)json_flt_idx(v, g->jend, 2);
	return (o);
}

static void	apply_spec_gloss(t_glb *g, const char *mat, t_glb_mat *m)
{
	const char	*ext;
	const char	*sg;

	ext = json_obj_find(mat, g->jend, "extensions");
	if (!ext)
		return ;
	sg = json_obj_find(ext, g->jend, "KHR_materials_pbrSpecularGlossiness");
	if (!sg)
		return ;
	m->color = read_vec3_factor(g, sg, "diffuseFactor", m->color);
	if (m->tex_id < 0)
		m->tex_id = glb_resolve_image(g, resolve_tex_image(g,
					tex_index_in_block(g, sg, "diffuseTexture")));
}

static void	load_one_material(t_glb *g, int idx)
{
	const char	*mat;
	const char	*pbr;
	const char	*ext;
	t_glb_mat	*m;

	m = &g->mats[idx];
	m->color = (t_vec3){1, 1, 1};
	m->emit = (t_vec3){0, 0, 0};
	m->emit_pow = 0.0f;
	m->tex_id = -1;
	m->emit_tex_id = -1;
	m->unlit = 0;
	mat = json_arr_get(json_obj_find(g->json, g->jend, "materials"),
			g->jend, idx);
	if (!mat)
		return ;
	pbr = json_obj_find(mat, g->jend, "pbrMetallicRoughness");
	m->color = read_vec3_factor(g, pbr, "baseColorFactor", m->color);
	m->tex_id = glb_resolve_image(g, resolve_tex_image(g,
				tex_index_in_block(g, pbr, "baseColorTexture")));
	apply_spec_gloss(g, mat, m);
	m->emit = read_vec3_factor(g, mat, "emissiveFactor", m->emit);
	m->emit_tex_id = glb_resolve_image(g, resolve_tex_image(g,
				tex_index_in_block(g, mat, "emissiveTexture")));
	if (m->emit_tex_id >= 0 || v3_dot(m->emit, m->emit) > 1e-6f)
	{
		m->emit_pow = 1.0f;
		if (v3_dot(m->emit, m->emit) <= 1e-6f)
			m->emit = (t_vec3){1, 1, 1};
	}
	ext = json_obj_find(mat, g->jend, "extensions");
	if (ext && json_obj_find(ext, g->jend, "KHR_materials_unlit"))
		m->unlit = 1;
}

void	glb_load_materials(t_glb *g)
{
	const char	*arr;
	int			i;

	arr = json_obj_find(g->json, g->jend, "materials");
	g->n_mats = arr ? json_count_array(arr, g->jend) : 0;
	arr = json_obj_find(g->json, g->jend, "images");
	g->n_imgs = arr ? json_count_array(arr, g->jend) : 0;
	if (g->n_imgs > 0)
	{
		g->img_tex = (int *)malloc(sizeof(int) * g->n_imgs);
		i = -1;
		while (g->img_tex && ++i < g->n_imgs)
			g->img_tex[i] = -1;
	}
	if (g->n_mats > 0)
		g->mats = (t_glb_mat *)calloc(g->n_mats, sizeof(t_glb_mat));
	i = -1;
	while (g->mats && ++i < g->n_mats)
		load_one_material(g, i);
}

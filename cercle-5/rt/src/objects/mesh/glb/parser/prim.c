/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "material.h"
#include "scene.h"
#include "skeletal.h"

typedef struct s_prim_data
{
	float			*pos;
	float			*uv;
	float			*wgt;
	unsigned int	*joi;
	unsigned int	*idx;
	int				n_verts;
	int				n_tris;
	int				mat_idx;
	int				node_idx;
	int				skin_idx;
}					t_prim_data;

static int	read_attrs(t_glb *g, const char *prim, t_prim_data *d)
{
	const char	*attrs;
	const char	*v;
	int			n;
	int			ne;

	attrs = json_obj_find(prim, g->jend, "attributes");
	if (!attrs)
		return (-1);
	v = json_obj_find(attrs, g->jend, "POSITION");
	if (!v)
		return (-1);
	d->pos = glb_read_float(g, (int)json_int(v, g->jend), &d->n_verts, &ne);
	if (!d->pos || ne != 3)
		return (-1);
	v = json_obj_find(attrs, g->jend, "TEXCOORD_0");
	if (v)
		d->uv = glb_read_float(g, (int)json_int(v, g->jend), &n, &ne);
	if (d->skin_idx >= 0)
	{
		v = json_obj_find(attrs, g->jend, "JOINTS_0");
		if (v)
			d->joi = glb_read_uint(g, (int)json_int(v, g->jend), &n, &ne);
		v = json_obj_find(attrs, g->jend, "WEIGHTS_0");
		if (v)
			d->wgt = glb_read_float(g, (int)json_int(v, g->jend), &n, &ne);
	}
	return (0);
}

static int	read_indices(t_glb *g, const char *prim, t_prim_data *d)
{
	const char	*v;
	int			n;
	int			ne;
	int			k;

	v = json_obj_find(prim, g->jend, "indices");
	if (v)
	{
		d->idx = glb_read_uint(g, (int)json_int(v, g->jend), &n, &ne);
		if (!d->idx)
			return (-1);
		d->n_tris = n / 3;
		return (0);
	}
	d->idx = (unsigned int *)malloc(sizeof(unsigned int) * d->n_verts);
	if (!d->idx)
		return (-1);
	k = -1;
	while (++k < d->n_verts)
		d->idx[k] = (unsigned int)k;
	d->n_tris = d->n_verts / 3;
	return (0);
}

static t_vec3	skin_bind(t_glb *g, t_prim_data *d, int v_idx, t_vec3 pl)
{
	t_anim_skin		*sk;
	t_vec3			acc;
	t_vec3			tmp;
	float			w_sum;
	float			w;
	unsigned int	j;
	int				i;

	sk = &g->anim->skins[d->skin_idx];
	acc = (t_vec3){0, 0, 0};
	w_sum = 0.0f;
	i = -1;
	while (++i < 4)
	{
		j = d->joi[v_idx * 4 + i];
		w = d->wgt[v_idx * 4 + i];
		if (w <= 0.0f || (int)j >= sk->n_joints
			|| sk->joints[j] < 0 || sk->joints[j] >= g->anim->n_nodes)
			continue ;
		tmp = skel_m4_xform_pos(&sk->ibm[j * 16], pl);
		tmp = skel_m4_xform_pos(g->anim->nodes[sk->joints[j]].bind_world, tmp);
		acc = v3_add(acc, v3_mul(tmp, w));
		w_sum += w;
	}
	if (w_sum <= 1e-6f && d->node_idx >= 0
		&& d->node_idx < g->anim->n_nodes)
		return (skel_m4_xform_pos(g->anim->nodes[d->node_idx].bind_world, pl));
	return (acc);
}

static t_vec3	bind_pos(t_glb *g, t_prim_data *d, int v_idx)
{
	t_vec3	pl;

	pl = (t_vec3){d->pos[v_idx * 3], d->pos[v_idx * 3 + 1],
		d->pos[v_idx * 3 + 2]};
	if (d->skin_idx >= 0 && d->joi && d->wgt && g->anim
		&& d->skin_idx < g->anim->n_skins)
		return (skin_bind(g, d, v_idx, pl));
	if (g->anim && d->node_idx >= 0 && d->node_idx < g->anim->n_nodes)
		return (skel_m4_xform_pos(g->anim->nodes[d->node_idx].bind_world, pl));
	return (pl);
}

static void	apply_material(t_object *o, t_glb *g, int mat_idx)
{
	t_glb_mat	*m;

	mat_init_default(&o->mat, g->color);
	o->mat.emit_color = g->emit;
	o->mat.emit_power = g->emit_power;
	if (mat_idx < 0 || mat_idx >= g->n_mats || !g->mats)
		return ;
	m = &g->mats[mat_idx];
	o->color = m->color;
	o->mat.albedo = m->color;
	o->mat.tex_id = m->tex_id;
	o->mat.emit_tex_id = m->emit_tex_id;
	if (m->emit_pow > 0.0f)
	{
		o->mat.emit_color = m->emit;
		o->mat.emit_power = m->emit_pow;
	}
	if (m->unlit)
	{
		o->mat.ks = 0;
		o->mat.reflectivity = 0;
		o->mat.roughness = 1.0f;
	}
}

static void	emit_one_tri(t_glb *g, t_prim_data *d, int t_idx)
{
	t_object		*o;
	unsigned int	tri[3];
	t_vec3			va;
	t_vec3			vb;
	t_vec3			vc;

	tri[0] = d->idx[t_idx * 3];
	tri[1] = d->idx[t_idx * 3 + 1];
	tri[2] = d->idx[t_idx * 3 + 2];
	o = scene_push_bvh(g->scene);
	if (!o)
		return ;
	o->type = OBJ_TRIANGLE;
	o->group_id = g->group_id;
	if ((int)tri[0] >= d->n_verts || (int)tri[1] >= d->n_verts
		|| (int)tri[2] >= d->n_verts)
	{
		o->u.tri.a = (t_vec3){0, 0, 0};
		o->u.tri.b = (t_vec3){0, 0, 0};
		o->u.tri.c = (t_vec3){0, 0, 0};
		o->u.tri.n = (t_vec3){0, 1, 0};
		apply_material(o, g, d->mat_idx);
		return ;
	}
	va = glb_apply_outer(g, bind_pos(g, d, (int)tri[0]));
	vb = glb_apply_outer(g, bind_pos(g, d, (int)tri[1]));
	vc = glb_apply_outer(g, bind_pos(g, d, (int)tri[2]));
	o->u.tri.a = va;
	o->u.tri.b = vb;
	o->u.tri.c = vc;
	o->u.tri.n = v3_norm(v3_cross(v3_sub(vb, va), v3_sub(vc, va)));
	if (d->uv)
	{
		o->u.tri.uv[0] = d->uv[tri[0] * 2];
		o->u.tri.uv[1] = d->uv[tri[0] * 2 + 1];
		o->u.tri.uv[2] = d->uv[tri[1] * 2];
		o->u.tri.uv[3] = d->uv[tri[1] * 2 + 1];
		o->u.tri.uv[4] = d->uv[tri[2] * 2];
		o->u.tri.uv[5] = d->uv[tri[2] * 2 + 1];
	}
	apply_material(o, g, d->mat_idx);
}

static void	register_anim_prim(t_glb *g, t_prim_data *d, int bvh_first)
{
	t_animator	*a;
	t_anim_prim	*p;
	t_anim_prim	*tmp;

	a = g->anim;
	tmp = (t_anim_prim *)realloc(a->prims,
			sizeof(t_anim_prim) * (a->n_prims + 1));
	if (!tmp)
		return ;
	a->prims = tmp;
	p = &a->prims[a->n_prims++];
	memset(p, 0, sizeof(*p));
	p->positions = d->pos;
	p->uvs = d->uv;
	p->weights = d->wgt;
	p->joints = d->joi;
	p->indices = d->idx;
	p->n_verts = d->n_verts;
	p->n_tris = d->n_tris;
	p->node = d->node_idx;
	p->skin = d->skin_idx;
	p->bvh_base = bvh_first;
	p->tex_id = (d->mat_idx >= 0 && d->mat_idx < g->n_mats)
		? g->mats[d->mat_idx].tex_id : -1;
	p->color = (d->mat_idx >= 0 && d->mat_idx < g->n_mats)
		? g->mats[d->mat_idx].color : (t_vec3){1, 1, 1};
	d->pos = NULL;
	d->uv = NULL;
	d->wgt = NULL;
	d->joi = NULL;
	d->idx = NULL;
}

static void	prim_data_free(t_prim_data *d)
{
	free(d->pos);
	free(d->uv);
	free(d->wgt);
	free(d->joi);
	free(d->idx);
}

void	glb_capture_prim(t_glb *g, const char *prim, int node_idx,
		int skin_idx)
{
	t_prim_data	d;
	const char	*v;
	int			i;
	int			bvh_first;

	memset(&d, 0, sizeof(d));
	d.mat_idx = -1;
	d.node_idx = node_idx;
	d.skin_idx = skin_idx;
	v = json_obj_find(prim, g->jend, "material");
	if (v)
		d.mat_idx = (int)json_int(v, g->jend);
	if (read_attrs(g, prim, &d) < 0 || read_indices(g, prim, &d) < 0)
	{
		prim_data_free(&d);
		return ;
	}
	if (d.skin_idx >= 0 && (!d.joi || !d.wgt))
		d.skin_idx = -1;
	bvh_first = (int)g->scene->n_bvh;
	i = -1;
	while (++i < d.n_tris)
		emit_one_tri(g, &d, i);
	if (g->anim)
		register_anim_prim(g, &d, bvh_first);
	prim_data_free(&d);
}

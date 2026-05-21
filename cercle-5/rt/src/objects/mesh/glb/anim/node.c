/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "skeletal.h"

static void	read_trs(const char *node, const char *jend, t_anim_node *o)
{
	const char	*v;

	o->t = (t_vec3){0, 0, 0};
	o->r = (t_vec4){{0, 0, 0, 1}};
	o->s = (t_vec3){1, 1, 1};
	o->has_matrix = 0;
	v = json_obj_find(node, jend, "matrix");
	if (v)
	{
		o->has_matrix = 1;
		json_flt_idx(v, jend, 0);
		{
			int	i;

			i = -1;
			while (++i < 16)
				o->local_mat[i] = (float)json_flt_idx(v, jend, i);
		}
		o->bt = o->t;
		o->br = o->r;
		o->bs = o->s;
		return ;
	}
	v = json_obj_find(node, jend, "translation");
	if (v)
		o->t = (t_vec3){(float)json_flt_idx(v, jend, 0),
			(float)json_flt_idx(v, jend, 1),
			(float)json_flt_idx(v, jend, 2)};
	v = json_obj_find(node, jend, "rotation");
	if (v)
		o->r = (t_vec4){{(float)json_flt_idx(v, jend, 0),
			(float)json_flt_idx(v, jend, 1),
			(float)json_flt_idx(v, jend, 2),
			(float)json_flt_idx(v, jend, 3)}};
	v = json_obj_find(node, jend, "scale");
	if (v)
		o->s = (t_vec3){(float)json_flt_idx(v, jend, 0),
			(float)json_flt_idx(v, jend, 1),
			(float)json_flt_idx(v, jend, 2)};
	o->bt = o->t;
	o->br = o->r;
	o->bs = o->s;
}

static void	link_children(const t_glb *g, const char *node, int parent,
		t_animator *a)
{
	const char	*ch;
	int			n;
	int			i;
	int			ci;

	ch = json_obj_find(node, g->jend, "children");
	if (!ch)
		return ;
	n = json_arr_len(ch, g->jend);
	i = -1;
	while (++i < n)
	{
		ci = (int)json_int_idx(ch, g->jend, i);
		if (ci >= 0 && ci < a->n_nodes)
			a->nodes[ci].parent = parent;
	}
}

static void	snapshot_bind(t_animator *a)
{
	int	i;

	skel_compute_world(a);
	i = -1;
	while (++i < a->n_nodes)
	{
		memcpy(a->nodes[i].bind_world, a->nodes[i].world,
			sizeof(float) * 16);
		if (skel_m4_inverse(a->nodes[i].bind_world,
				a->nodes[i].bind_world_inv) != 0)
			skel_m4_identity(a->nodes[i].bind_world_inv);
	}
}

void	glb_capture_nodes(t_glb *g)
{
	const char	*nodes;
	t_animator	*a;
	int			i;

	a = g->anim;
	nodes = json_obj_find(g->json, g->jend, "nodes");
	if (!nodes)
		return ;
	a->n_nodes = json_arr_len(nodes, g->jend);
	if (a->n_nodes <= 0)
		return ;
	a->nodes = (t_anim_node *)calloc(a->n_nodes, sizeof(t_anim_node));
	if (!a->nodes)
	{
		a->n_nodes = 0;
		return ;
	}
	i = -1;
	while (++i < a->n_nodes)
	{
		a->nodes[i].parent = -1;
		read_trs(json_arr_get(nodes, g->jend, i), g->jend, &a->nodes[i]);
	}
	i = -1;
	while (++i < a->n_nodes)
		link_children(g, json_arr_get(nodes, g->jend, i), i, a);
	snapshot_bind(a);
}

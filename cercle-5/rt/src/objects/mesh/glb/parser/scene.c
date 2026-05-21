/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:23:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "skeletal.h"

static void	emit_node_mesh(t_glb *g, int node_idx, int mesh_idx, int skin_idx)
{
	const char	*mesh;
	const char	*prims;
	const char	*prim;
	int			n;
	int			i;

	mesh = json_arr_get(json_obj_find(g->json, g->jend, "meshes"),
			g->jend, mesh_idx);
	if (!mesh)
		return ;
	prims = json_obj_find(mesh, g->jend, "primitives");
	if (!prims)
		return ;
	n = json_arr_len(prims, g->jend);
	i = -1;
	while (++i < n)
	{
		prim = json_arr_get(prims, g->jend, i);
		if (prim)
			glb_capture_prim(g, prim, node_idx, skin_idx);
	}
}

static void	walk_node(t_glb *g, int node_idx)
{
	const char	*node;
	const char	*v;
	const char	*children;
	int			n;
	int			i;
	int			skin_idx;

	node = json_arr_get(json_obj_find(g->json, g->jend, "nodes"),
			g->jend, node_idx);
	if (!node)
		return ;
	v = json_obj_find(node, g->jend, "mesh");
	if (v)
	{
		skin_idx = -1;
		if (json_obj_find(node, g->jend, "skin"))
			skin_idx = (int)json_int(json_obj_find(node, g->jend, "skin"),
					g->jend);
		emit_node_mesh(g, node_idx, (int)json_int(v, g->jend), skin_idx);
	}
	children = json_obj_find(node, g->jend, "children");
	if (!children)
		return ;
	n = json_arr_len(children, g->jend);
	i = -1;
	while (++i < n)
		walk_node(g, (int)json_int_idx(children, g->jend, i));
}

static int	pick_scene_index(const t_glb *g)
{
	const char	*v;

	v = json_obj_find(g->json, g->jend, "scene");
	if (v)
		return ((int)json_int(v, g->jend));
	return (0);
}

void	glb_walk_scene(t_glb *g)
{
	const char	*scenes;
	const char	*scene;
	const char	*roots;
	int			n;
	int			i;

	scenes = json_obj_find(g->json, g->jend, "scenes");
	scene = NULL;
	if (scenes)
	{
		scene = json_arr_get(scenes, g->jend, pick_scene_index(g));
		if (!scene)
			scene = json_arr_get(scenes, g->jend, 0);
	}
	roots = scene ? json_obj_find(scene, g->jend, "nodes") : NULL;
	if (!roots && g->anim)
	{
		i = -1;
		while (++i < g->anim->n_nodes)
			if (g->anim->nodes[i].parent < 0)
				walk_node(g, i);
		return ;
	}
	if (!roots)
		return ;
	n = json_arr_len(roots, g->jend);
	i = -1;
	while (++i < n)
		walk_node(g, (int)json_int_idx(roots, g->jend, i));
}

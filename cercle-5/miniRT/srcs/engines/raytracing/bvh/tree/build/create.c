/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 16:48:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	flatten_tmp(t_bvh_tmp_node *node, t_bvh *bvh, size_t *nc,
		size_t *rc)
{
	size_t	my_idx;

	my_idx = (*nc)++;
	bvh->nodes[my_idx].bbox = node->bbox;
	if (node->num_refs > 0)
	{
		bvh->nodes[my_idx].count = node->num_refs;
		bvh->nodes[my_idx].left_or_first = *rc;
		while (node->num_refs--)
			bvh->refs[(*rc)++] = node->refs[node->num_refs];
	}
	else
	{
		bvh->nodes[my_idx].count = 0;
		flatten_tmp(node->left, bvh, nc, rc);
		bvh->nodes[my_idx].left_or_first = *nc;
		flatten_tmp(node->right, bvh, nc, rc);
	}
}

static t_bvh_tmp_node	*build_tmp_tree(t_scene *scene, size_t total, size_t *k)
{
	t_build_item	*items;
	t_bvh_tmp_node	*root;
	size_t			i;

	i = 0;
	while (i < scene->cylinder_count)
		cylinder_precompute(&scene->cylinders[i++]);
	i = 0;
	while (i < scene->pyramid_count)
		pyramid_cache_verts(&scene->pyramids[i++]);
	items = ft_calloc(total, sizeof(t_build_item));
	if (!items)
		return (NULL);
	*k = collect_objects_worker(scene, items);
	root = build_recursive(items, *k);
	free(items);
	return (root);
}

static size_t	get_scene_total(t_scene *scene)
{
	size_t	total;
	size_t	i;
	size_t	dead;

	/* Planes are infinite and excluded from BVH — check them separately */
	total = scene->sphere_count;
	total += scene->cylinder_count + scene->cone_count;
	total += scene->mesh_count + scene->anim_count;
	total += scene->tri_count + scene->rect_count;
	total += scene->pyramid_count + scene->box_count;
	total += scene->capsule_count;
	dead = 0;
	i = scene->proxy_sphere_base;
	while (i < scene->sphere_count)
	{
		if (scene->spheres[i].radius_sq <= 0.0)
			dead++;
		i++;
	}
	if (dead > total)
		dead = total;
	return (total - dead);
}

static void	bvh_finalize(t_bvh *bvh, t_bvh_tmp_node *root)
{
	size_t	nc;
	size_t	rc;

	nc = 0;
	rc = 0;
	flatten_tmp(root, bvh, &nc, &rc);
	bvh->num_nodes = nc;
	bvh->num_refs = rc;
	node_destroy(root);
	bvh_collapse(bvh);
}

t_bvh	*bvh_create(t_scene *scene)
{
	t_bvh			*bvh;
	t_bvh_tmp_node	*root;
	size_t			k;

	if (!scene || get_scene_total(scene) == 0)
		return (NULL);
	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	root = build_tmp_tree(scene, get_scene_total(scene), &k);
	if (!root || k == 0)
		return (node_destroy(root), free(bvh), NULL);
	bvh->nodes = ft_calloc(2 * k + 1, sizeof(t_bvh_node));
	bvh->refs = ft_calloc(k + 1, sizeof(t_bvh_ref));
	if (!bvh->nodes || !bvh->refs)
	{
		(free(bvh->nodes), free(bvh->refs), free(bvh));
		return (node_destroy(root), NULL);
	}
	bvh_finalize(bvh, root);
#ifdef DEBUG_EXTENDER
	fprintf(stderr, "[BVH] nodes=%zu refs=%zu root_count=%zu root_first=%zu\n",
		bvh->num_nodes, bvh->num_refs,
		bvh->nodes[0].count, bvh->nodes[0].left_or_first);
#endif
	build_emissive_cache(scene);
	return (bvh);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/04 20:46:54 by abdoali          ###   ########.fr       */
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

	total = scene->sphere_count + scene->plane_count;
	total += scene->cylinder_count + scene->cone_count;
	total += scene->mesh_count + scene->anim_count;
	total += scene->tri_count + scene->rect_count;
	total += scene->pyramid_count + scene->box_count;
	total += scene->capsule_count;
	return (total);
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
	build_emissive_cache(scene);
	return (bvh);
}

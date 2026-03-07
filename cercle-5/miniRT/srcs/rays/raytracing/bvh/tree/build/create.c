/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 03:07:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 03:07:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static void	flatten_tmp(t_bvh_tmp_node *node, t_bvh *bvh, int *nc, int *rc)
{
	int		my_idx;
	int		right_idx;
	size_t	i;

	my_idx = (*nc)++;
	bvh->nodes[my_idx].bbox = node->bbox;
	if (node->num_refs > 0)
	{
		bvh->nodes[my_idx].count = (int)node->num_refs;
		bvh->nodes[my_idx].left_or_first = *rc;
		i = 0;
		while (i < node->num_refs)
			bvh->refs[(*rc)++] = node->refs[i++];
	}
	else
	{
		bvh->nodes[my_idx].count = 0;
		flatten_tmp(node->left, bvh, nc, rc);
		right_idx = *nc;
		flatten_tmp(node->right, bvh, nc, rc);
		bvh->nodes[my_idx].left_or_first = right_idx;
	}
}

static t_bvh_tmp_node	*build_tmp_tree(t_scene *scene, size_t total, size_t *k)
{
	t_build_item	*items;
	t_bvh_tmp_node	*root;

	items = malloc(sizeof(t_build_item) * total);
	if (!items)
		return (NULL);
	*k = collect_objects(scene, items);
	root = build_recursive(items, *k);
	free(items);
	return (root);
}

static int	alloc_flat(t_bvh *bvh, size_t k)
{
	bvh->nodes = malloc(sizeof(t_bvh_node) * (2 * k + 1));
	bvh->refs = malloc(sizeof(t_bvh_ref) * (k + 1));
	if (!bvh->nodes || !bvh->refs)
	{
		free(bvh->nodes);
		free(bvh->refs);
		return (0);
	}
	return (1);
}

t_bvh	*bvh_create(t_scene *scene)
{
	t_bvh			*bvh;
	t_bvh_tmp_node	*root;
	size_t			total;
	size_t			k;
	int				nc;
	int				rc;

	if (!scene)
		return (NULL);
	bvh = ft_calloc(1, sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	total = (size_t)scene->sphere_count + scene->plane_count
		+ scene->cylinder_count + scene->cone_count
		+ scene->mesh_count + scene->anim_count;
	if (total == 0)
		return (bvh);
	root = build_tmp_tree(scene, total, &k);
	if (!root)
		return (free(bvh), NULL);
	if (!alloc_flat(bvh, k))
	{
		node_destroy(root);
		return (free(bvh), NULL);
	}
	nc = 0;
	rc = 0;
	flatten_tmp(root, bvh, &nc, &rc);
	bvh->num_nodes = nc;
	bvh->num_refs = rc;
	node_destroy(root);
	return (bvh);
}

void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh)
		return ;
	free(bvh->nodes);
	free(bvh->refs);
	free(bvh);
}

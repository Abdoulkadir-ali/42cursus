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

/*
** Macro: is a material emission strong enough to count as an emissive light?
*/
# define IS_EMISSIVE(sc, mat_id) \
	((mat_id) >= 0 && (mat_id) < (sc)->mat_count \
	&& ((sc)->materials[(mat_id)].emission.x * (sc)->materials[(mat_id)].emission.x \
	  + (sc)->materials[(mat_id)].emission.y * (sc)->materials[(mat_id)].emission.y \
	  + (sc)->materials[(mat_id)].emission.z * (sc)->materials[(mat_id)].emission.z) > 1.0)

static void	build_emissive_cache(t_scene *sc)
{
	t_emissive_ref	*cache;
	int				cap;
	int				n;
	int				i;

	free(sc->emissive_cache);
	sc->emissive_cache = NULL;
	sc->emissive_n = 0;
	cap = sc->sphere_count + sc->tri_count + sc->rect_count
		+ sc->pyramid_count + sc->box_count + sc->capsule_count
		+ sc->mesh_count;
	if (cap == 0)
		return ;
	cache = malloc(sizeof(t_emissive_ref) * cap);
	if (!cache)
		return ;
	n = 0;
	i = -1;
	while (++i < sc->sphere_count)
		if (IS_EMISSIVE(sc, sc->spheres[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_SPHERE, i};
	i = -1;
	while (++i < sc->tri_count)
		if (IS_EMISSIVE(sc, sc->tris[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_TRI, i};
	i = -1;
	while (++i < sc->rect_count)
		if (IS_EMISSIVE(sc, sc->rects[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_RECT, i};
	i = -1;
	while (++i < sc->pyramid_count)
		if (IS_EMISSIVE(sc, sc->pyramids[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_PYRAMID, i};
	i = -1;
	while (++i < sc->box_count)
		if (IS_EMISSIVE(sc, sc->boxes[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_BOX, i};
	i = -1;
	while (++i < sc->capsule_count)
		if (IS_EMISSIVE(sc, sc->capsules[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_CAPSULE, i};
	i = -1;
	while (++i < sc->mesh_count)
		if (IS_EMISSIVE(sc, sc->meshes[i].mat_id))
			cache[n++] = (t_emissive_ref){TYPE_MESH, i};
	sc->emissive_cache = cache;
	sc->emissive_n = n;
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
		+ scene->mesh_count + scene->anim_count
		+ scene->tri_count + scene->rect_count
		+ scene->pyramid_count + scene->box_count
		+ scene->capsule_count;
	if (total == 0)
		return (bvh);
	root = build_tmp_tree(scene, total, &k);
	if (!root)
		return (free(bvh), NULL);
	if (k == 0)
	{
		node_destroy(root);
		return (bvh);
	}
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
	k = 0;
	while ((int)k < scene->pyramid_count)
	{
		pyramid_cache_verts(&scene->pyramids[k]);
		k++;
	}
	build_emissive_cache(scene);
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

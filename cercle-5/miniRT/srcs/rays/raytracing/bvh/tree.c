/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static int	compare_x(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	return (ia->centroid.x < ib->centroid.x ? -1 : ia->centroid.x > ib->centroid.x);
}

static int	compare_y(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	return (ia->centroid.y < ib->centroid.y ? -1 : ia->centroid.y > ib->centroid.y);
}

static int	compare_z(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	return (ia->centroid.z < ib->centroid.z ? -1 : ia->centroid.z > ib->centroid.z);
}

static void	node_destroy(t_bvh_node *node);

static t_bvh_node	*init_leaf_node(t_build_item *items, size_t count)
{
	t_bvh_node	*node;
	size_t		i;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node) return (NULL);
	node->bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		node->bbox = aabb_union(&node->bbox, &items[i++].bbox);
	node->bbox.min = vec3_sub(node->bbox.min, vec3(1e-5, 1e-5, 1e-5));
	node->bbox.max = vec3_add(node->bbox.max, vec3(1e-5, 1e-5, 1e-5));
	node->refs = malloc(sizeof(t_bvh_ref) * count);
	if (!node->refs) return (free(node), NULL);
	i = 0;
	while (i < count) {
		node->refs[i] = items[i].ref;
		i++;
	}
	node->num_refs = count;
	return (node);
}




static t_bvh_node	*build_recursive(t_build_item *items, size_t count)
{
	t_bvh_node	*node;
	double		min_cost;
	int			best_axis;
	size_t		best_split;
	int			axis;
	size_t		i;
	t_aabb		left_box, right_box;
	double		cost, p_area;

	node = ft_calloc(1, sizeof(t_bvh_node));
	if (!node) return (NULL);
	node->bbox = aabb_create_empty();
	i = 0;
	while (i < count)
		node->bbox = aabb_union(&node->bbox, &items[i++].bbox);
	node->bbox.min = vec3_sub(node->bbox.min, vec3(1e-5, 1e-5, 1e-5));
	node->bbox.max = vec3_add(node->bbox.max, vec3(1e-5, 1e-5, 1e-5));
	
	/* SAH Constants */
	const double	t_cost = 1.0;
	const double	i_cost = 2.0;

	if (count <= MAX_LEAF_OBJECTS)
	{
		free(node);
		return (init_leaf_node(items, count));
	}

	min_cost = count * i_cost; /* Cost if we make a leaf */
	best_axis = -1;
	best_split = -1;
	p_area = aabb_surface_area(node->bbox);

	/* Evaluate all 3 axes */
	axis = 0;
	while (axis < 3)
	{
		if (axis == 0) qsort(items, count, sizeof(t_build_item), compare_x);
		else if (axis == 1) qsort(items, count, sizeof(t_build_item), compare_y);
		else qsort(items, count, sizeof(t_build_item), compare_z);

		
		/* Better Algorithm: Binned SAH with 128 bins (high res) + Termination Check */
		for (int s = 1; s < 32; s++)
		{
			size_t split = (count * s) / 32;
			if (split < 1 || split >= count) continue;

			left_box = aabb_create_empty();
			right_box = aabb_create_empty();
			
			for (size_t k = 0; k < split; k++) left_box = aabb_union(&left_box, &items[k].bbox);
			for (size_t k = split; k < count; k++) right_box = aabb_union(&right_box, &items[k].bbox);
			
			cost = t_cost + (aabb_surface_area(left_box) / p_area) * split * i_cost + \
					(aabb_surface_area(right_box) / p_area) * (count - split) * i_cost;
			
			if (cost < min_cost) {
				min_cost = cost;
				best_axis = axis;
				best_split = split;
			}
		}
		axis++;
	}

	/* Termination: If splitting is more expensive than leaf, make leaf */
	if (best_axis == -1) /* min_cost never improved over leaf cost */
	{
		free(node);
		return (init_leaf_node(items, count));
	}

	if (best_axis == 0) qsort(items, count, sizeof(t_build_item), compare_x);
	else if (best_axis == 1) qsort(items, count, sizeof(t_build_item), compare_y);
	/* If best_axis == 2, items are already sorted by Z from the last iteration */
	
	node->left = build_recursive(items, best_split);
	if (!node->left) { free(node); return (NULL); }
	node->right = build_recursive(items + best_split, count - best_split);
	if (!node->right) { node_destroy(node->left); free(node); return (NULL); }
	
	return (node);
}

static t_vec3	get_centroid(const t_aabb *bbox)
{
	return (vec3_scale(vec3_add(bbox->min, bbox->max), 0.5));
}

static size_t	collect_objects(t_scene *scene, t_build_item *items)
{
	size_t	k = 0;
	int		i = 0;
	while (i < scene->sphere_count) {
		items[k].ref = (t_bvh_ref){TYPE_SPHERE, i++};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox); k++;
	}
	i = 0;
	while (i < scene->cylinder_count) {
		items[k].ref = (t_bvh_ref){TYPE_CYLINDER, i++};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox); k++;
	}
	i = 0;
	while (i < scene->cone_count) {
		items[k].ref = (t_bvh_ref){TYPE_CONE, i++};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox); k++;
	}
	return (k);
}

static size_t	collect_complex(t_scene *scene, t_build_item *items, size_t k)
{
	int	i = 0;
	while (i < scene->mesh_count) {
		items[k].ref = (t_bvh_ref){TYPE_MESH, i++};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox); k++;
	}
	i = 0;
	while (i < scene->anim_count) {
		items[k].ref = (t_bvh_ref){TYPE_ANIM, i++};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox); k++;
	}
	return (k);
}

t_bvh	*bvh_create(t_scene *scene)
{
	t_bvh *bvh; t_build_item *items; size_t total, k;
	if (!scene) return (NULL);
	bvh = malloc(sizeof(t_bvh)); if (!bvh) return (NULL);
	bvh->scene = scene;
	total = scene->sphere_count + scene->cylinder_count + scene->cone_count
		+ scene->mesh_count + scene->anim_count;
	if (total == 0) { bvh->root = NULL; return (bvh); }
	items = malloc(sizeof(t_build_item) * total);
	if (!items) return (free(bvh), NULL);
	k = collect_objects(scene, items);
	k = collect_complex(scene, items, k);
	bvh->root = build_recursive(items, k);
	return (free(items), bvh);
}

static void	node_destroy(t_bvh_node *node)
{
	if (!node) return ;
	node_destroy(node->left);
	node_destroy(node->right);
	if (node->refs) free(node->refs);
	free(node);
}

void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh) return ;
	node_destroy(bvh->root);
	free(bvh);
}

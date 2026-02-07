/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"
#include "scene.h"

typedef struct s_build_item
{
	t_bvh_ref	ref;
	t_aabb		bbox;
	t_vec3		centroid;
}				t_build_item;

static int	compare_x(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	if (ia->centroid.x < ib->centroid.x) return (-1);
	if (ia->centroid.x > ib->centroid.x) return (1);
	return (0);
}

static int	compare_y(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	if (ia->centroid.y < ib->centroid.y) return (-1);
	if (ia->centroid.y > ib->centroid.y) return (1);
	return (0);
}

static int	compare_z(const void *a, const void *b)
{
	t_build_item	*ia = (t_build_item *)a;
	t_build_item	*ib = (t_build_item *)b;
	if (ia->centroid.z < ib->centroid.z) return (-1);
	if (ia->centroid.z > ib->centroid.z) return (1);
	return (0);
}

static t_bvh_node	*build_recursive(t_build_item *items, size_t count)
{
	t_bvh_node	*node;
	size_t		i;

	node = malloc(sizeof(t_bvh_node));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(t_bvh_node));

	// Compute Node BBox
	node->bbox = aabb_create_empty();
	for (i = 0; i < count; i++)
		node->bbox = aabb_union(&node->bbox, &items[i].bbox);

	// Leaf condition
	if (count <= MAX_LEAF_OBJECTS)
	{
		node->refs = malloc(sizeof(t_bvh_ref) * count);
		if (!node->refs)
		{
			free(node);
			return (NULL);
		}
		for (i = 0; i < count; i++)
			node->refs[i] = items[i].ref;
		node->num_refs = count;
		return (node);
	}

	// Split
	t_vec3 span = vec3_sub(node->bbox.max, node->bbox.min);
	int (*comp)(const void *, const void *);
	if (span.x > span.y && span.x > span.z) comp = compare_x;
	else if (span.y > span.z) comp = compare_y;
	else comp = compare_z;

	qsort(items, count, sizeof(t_build_item), comp);

	size_t mid = count / 2;
	node->left = build_recursive(items, mid);
	node->right = build_recursive(items + mid, count - mid);
	return (node);
}

static t_vec3	get_centroid(const t_aabb *bbox)
{
	return (vec3_scale(vec3_add(bbox->min, bbox->max), 0.5));
}

t_bvh	*bvh_create(t_scene *scene)
{
	t_bvh			*bvh;
	t_build_item	*items;
	size_t			total;
	size_t			k;
	int				i;

	if (!scene)
		return (NULL);
	bvh = malloc(sizeof(t_bvh));
	if (!bvh)
		return (NULL);
	bvh->scene = scene;
	total = scene->sphere_count + scene->cylinder_count
		+ scene->mesh_count + scene->anim_count;
	
	if (total == 0)
	{
		bvh->root = NULL;
		return (bvh);
	}

	items = malloc(sizeof(t_build_item) * total);
	if (!items)
	{
		free(bvh);
		return (NULL);
	}

	k = 0;
	// Add Spheres
	for (i = 0; i < scene->sphere_count; i++)
	{
		items[k].ref = (t_bvh_ref){TYPE_SPHERE, i};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox);
		k++;
	}
	
	// Add Cylinders
	for (i = 0; i < scene->cylinder_count; i++)
	{
		items[k].ref = (t_bvh_ref){TYPE_CYLINDER, i};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox);
		k++;
	}
	// Add Meshes
	for (i = 0; i < scene->mesh_count; i++)
	{
		items[k].ref = (t_bvh_ref){TYPE_MESH, i};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox);
		k++;
	}
	// Add Animated
	for (i = 0; i < scene->anim_count; i++)
	{
		items[k].ref = (t_bvh_ref){TYPE_ANIM, i};
		items[k].bbox = aabb_from_ref(scene, items[k].ref);
		items[k].centroid = get_centroid(&items[k].bbox);
		k++;
	}
    if (k != total)
    {
        printf("Error: BVH Count Mismatch. Expected %zu, got %zu\n", total, k);
        total = k; 
    }

	bvh->root = build_recursive(items, total);
	free(items);
	return (bvh);
}

static void	node_destroy(t_bvh_node *node)
{
	if (!node)
		return ;
	node_destroy(node->left);
	node_destroy(node->right);
	if (node->refs)
		free(node->refs);
	free(node);
}

void	bvh_destroy(t_bvh *bvh)
{
	if (!bvh)
		return ;
	node_destroy(bvh->root);
	free(bvh);
}

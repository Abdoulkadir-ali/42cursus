/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

/* 1. EXTERNAL DEPENDENCIES */
# include "maths.h"
# include "types.h"
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

/* 2. CONSTANTS */
# define MAX_LEAF_OBJECTS 4

/* 3. MODULE TYPES */
struct					s_bvh_ref
{
	uint8_t				type;
	int					index;
};

struct					s_bvh_node
{
	t_aabb				bbox;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	t_bvh_ref			*refs;
	size_t				num_refs;
};

struct					s_bvh
{
	t_scene				*scene;
	t_bvh_node			*root;
};

/* srcs/raytracing/bvh/ */
t_bvh					*bvh_create(t_scene *scene);
void					bvh_destroy(t_bvh *bvh);
t_aabb					aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb					aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb					aabb_create_empty(void);

/* 5. IMPLEMENTATION IMPORTS */
# include "scene.h"

#endif

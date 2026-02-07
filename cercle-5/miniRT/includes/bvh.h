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

# include "objects/objects.h"
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <stdint.h>
# include <float.h>
# include <math.h>

# define MAX_LEAF_OBJECTS 4

typedef struct s_scene	t_scene;

typedef struct s_bvh_ref
{
	uint8_t		type;
	int			index;
}				t_bvh_ref;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
	t_bvh_ref			*refs;
	size_t				num_refs;
}						t_bvh_node;

typedef struct s_bvh
{
	t_scene				*scene;
	t_bvh_node			*root;
}						t_bvh;

// Functions
t_bvh		*bvh_create(t_scene *scene);
void		bvh_destroy(t_bvh *bvh);
t_aabb		aabb_from_ref(t_scene *s, t_bvh_ref ref);
t_aabb		aabb_union(const t_aabb *a, const t_aabb *b);
t_aabb		aabb_create_empty(void);

#endif

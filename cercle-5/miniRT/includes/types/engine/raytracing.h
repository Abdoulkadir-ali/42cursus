/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:50:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_RAYTRACING_H
# define TYPES_ENGINE_RAYTRACING_H

# include "maths.h"

typedef struct s_bvh_ref
{
	uint8_t				type;
	int					index;
}						t_bvh_ref;

typedef struct s_hit
{
	bool				hit;
	double				t;
	t_vec3				point;
	t_vec3				normal;
	t_vec3				v_normal;
	t_vec3				tangent;
	t_vec3				bitangent;
	t_vec2				uv;
	int					mat_id;
	t_bvh_ref			ref;
	void				*mesh;
	int					tri_idx;
	t_vec3				bary;
}						t_hit;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	int					left_or_first;
	int					count;
}						t_bvh_node;

typedef struct s_bvh_tmp_node
{
	t_aabb				bbox;
	struct s_bvh_tmp_node	*left;
	struct s_bvh_tmp_node	*right;
	t_bvh_ref			*refs;
	size_t				num_refs;
}						t_bvh_tmp_node;

typedef struct s_bvh
{
	struct s_scene		*scene;
	t_bvh_node			*nodes;
	t_bvh_ref			*refs;
	int					num_nodes;
	int					num_refs;
}						t_bvh;

typedef struct s_shading
{
	t_hit				*hit;
	struct s_scene		*scene;
	const t_bvh			*bvh;
	const t_ray			*ray;
	struct s_material	mat;
	t_vec3				albedo;
	t_vec3				aux_v;
}						t_shading;

typedef struct s_build_item
{
	t_bvh_ref			ref;
	t_aabb				bbox;
	t_vec3				centroid;
}						t_build_item;

typedef struct s_split_info
{
	int					axis;
	size_t				split;
	double				cost;
}						t_split_info;

#endif

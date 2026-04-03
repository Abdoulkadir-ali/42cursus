/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_raytracing.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 09:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:55:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_ENGINE_RAYTRACING_H
# define TYPES_ENGINE_RAYTRACING_H

# include "maths.h"

typedef struct s_entry_point
{
	t_vec3	p;
	t_vec3	center;
	double	radius;
	double	height;
	double	h;
}	t_entry_point;

typedef struct s_bvh_ref
{
	uint8_t				type;
	size_t				index;
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
	size_t				mat_id;
	t_bvh_ref			ref;
	void				*mesh;
	size_t				tri_idx;
	t_vec3				bary;
	double				u;
	double				v;
}						t_hit;

typedef struct s_trace
{
	t_hit				*hit;
	const struct s_mesh	*mesh;
	const t_ray			*ray;
	double				dist;
	size_t				stack[64];
	size_t				top;
	size_t				node_idx;
	size_t				best_tri;
	double				best_t;
	t_vec2				best_uv;
}						t_trace;

typedef struct s_bvh_node
{
	t_aabb				bbox;
	size_t				left_or_first;
	size_t				count;
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
	size_t				num_nodes;
	size_t				num_refs;
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

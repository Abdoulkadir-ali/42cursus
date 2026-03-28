/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:42:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "maths.h"
# include "surface.h"

typedef struct s_ambient
{
	double			brightness;
	t_vec3			rgb;
}					t_ambient;

typedef struct s_camera
{
	t_transform		transform;
	double			fov;
	double			aspect;
}					t_camera;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT
}					t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_transform		transform;
	double			brightness;
	t_vec3			rgb;
	double			cutoff;
}					t_light;

typedef struct s_sphere
{
	t_vec3			center;
	double			radius;
	int				mat_idx;
}					t_sphere;

typedef struct s_plane
{
	t_vec3			point;
	t_vec3			normal;
	int				mat_idx;
}					t_plane;

typedef struct s_cylinder
{
	t_vec3			pos;
	t_vec3			axis;
	double			radius;
	double			height;
	int				mat_idx;
}					t_cylinder;

typedef struct s_cone
{
	t_vec3			tip;
	t_vec3			axis;
	double			angle;
	double			height;
	int				mat_idx;
}					t_cone;

typedef struct s_box
{
	t_vec3			min;
	t_vec3			max;
	int				mat_idx;
}					t_box;

typedef struct s_capsule
{
	t_vec3			a;
	t_vec3			b;
	double			radius;
	int				mat_idx;
}					t_capsule;

typedef struct s_rect
{
	t_vec3			pos;
	t_vec3			normal;
	double			ex;
	double			ey;
	int				mat_idx;
}					t_rect;

typedef struct s_pyramid
{
	t_vec3			pos;
	t_vec3			up;
	double			size;
	double			height;
	int				mat_idx;
}					t_pyramid;

typedef struct s_tri_view
{
	t_vec3			v0;
	t_vec3			v1;
	t_vec3			v2;
	t_vec3			n;
	int				mat_idx;
}					t_tri_view;

typedef enum e_prim_type
{
	PRIM_NONE = 0,
	PRIM_SPHERE = 1,
	PRIM_PLANE = 2,
	PRIM_CYLINDER = 3,
	PRIM_CONE = 4,
	PRIM_TRIANGLE = 5,
	PRIM_RECT = 6,
	PRIM_BOX = 7,
	PRIM_CAPSULE = 8,
	PRIM_PYRAMID = 9
}					t_prim_type;

// Unified object type -- superset of e_prim_type
typedef enum e_type
{
	TYPE_NONE = 0,
	TYPE_SPHERE = 1,
	TYPE_PLANE = 2,
	TYPE_CYLINDER = 3,
	TYPE_CONE = 4,
	TYPE_TRI = 5,
	TYPE_RECT = 6,
	TYPE_BOX = 7,
	TYPE_CAPSULE = 8,
	TYPE_PYRAMID = 9,
	TYPE_MESH = 10,
	TYPE_ANIM = 11,
	TYPE_LIGHT = 12
}					t_type;

// BVH reference -- indexes into either primitives SoA or tri_soa
typedef struct s_bvh_ref
{
	t_type			type;
	int				index;
}					t_bvh_ref;

// Alias used in t_bvh node array
typedef t_bvh_ref	t_prim_ref;

typedef struct s_prim_params
{
	t_vec3			pos;
	t_vec3			axis;
	t_vec3			tangent;
	float			radius;
	float			height;
	t_vec3			extents;
	int				mat_id;
}					t_prim_params;

/**
 * @brief Unified Primitive Array in SoA (Structure of Arrays) layout.
 * Optimized with float precision for maximum SIMD throughput.
 */
typedef struct s_primitive_array
{
	uint8_t *types;     /* 1 byte per primitive: e_prim_type */
	float *px;          /* Position component X */
	float *py;          /* Position component Y */
	float *pz;          /* Position component Z */
	float *ax;          /* Normal/Axis component X */
	float *ay;          /* Normal/Axis component Y */
	float *az;          /* Normal/Axis component Z */
	float *tx;          /* Tangent component X */
	float *ty;          /* Tangent component Y */
	float *tz;          /* Tangent component Z */
	float *radii;       /* Sphere/Cyl/Capsule radii */
	float *heights;     /* Cyl/Capsule/Pyramid full heights */
	float *ex;          /* Extent X: half-width for Box/Rect/Pyramid */
	float *ey;          /* Extent Y: half-height for Box/Rect */
	float *ez;          /* Extent Z: half-depth for Box/Rect/Pyramid */
	uint16_t *mat_ids;  /* Material pool indices */
	uint8_t *is_static; /* 1 if object is static environment */
	uint8_t *has_phys;  /* 1 if object participates in physics */
	float *abb_min_x;   /* AABB cached world minimum X */
	float			*abb_min_y;
	float			*abb_min_z;
	float *abb_max_x; /* AABB cached world maximum X */
	float			*abb_max_y;
	float			*abb_max_z;
	int *phys_idx;   /* Link to physics SoA entry (-1 if none) */
	size_t count;    /* Active primitive count */
	size_t capacity; /* Allocated capacity */
}					t_primitive_array;

/**
 * @brief Structure of Arrays (SoA) for Triangles.
 * Uses float precision and parallel components for AVX/SSE batch processing.
 * Includes pre-computed world-space normals and tangents.
 */
typedef struct s_tri_array
{
	float			*vx[3];
	float			*vy[3];
	float			*vz[3];
	float			*ex[2];
	float			*ey[2];
	float			*ez[2];
	float *nx; /* Face normal components */
	float			*ny;
	float			*nz;
	float *tx; /* Surface tangent components */
	float			*ty;
	float			*tz;
	uint16_t		*mat_ids;
	size_t			count;
	size_t			cap;
}					t_tri_array;

/* Skinning weights for skeletal animation (GLB/FBX/OBJ) */
/* Defined here so t_primitive_array/t_tri_array sibling types stay together. */
typedef struct s_bone_weight
{
	uint16_t		bone_ids[4];
	float			weights[4];
}					t_bone_weight;

#endif

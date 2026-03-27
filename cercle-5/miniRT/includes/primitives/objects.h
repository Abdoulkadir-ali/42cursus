/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 19:26:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdint.h>
# include <stddef.h>
# include "maths.h"
# include "surface.h"

typedef struct s_ambient
{
	double		brightness;
	t_vec3		rgb;
}	t_ambient;

typedef struct s_camera
{
	t_transform	transform;
	double		fov;
	double		aspect;
}	t_camera;

typedef enum e_light_type
{
	LIGHT_POINT,
	LIGHT_SPOT
}	t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_transform		transform;
	double			brightness;
	t_vec3			rgb;
	double			cutoff;
}	t_light;

typedef enum e_prim_type
{
	PRIM_NONE,
	PRIM_SPHERE,
	PRIM_PLANE,
	PRIM_CYLINDER,
	PRIM_CONE,
	PRIM_TRIANGLE,
	PRIM_RECT,
	PRIM_BOX,
	PRIM_CAPSULE,
	PRIM_PYRAMID
}	t_prim_type;
 
typedef struct s_prim_params
{
	t_vec3		pos;
	t_vec3		axis;
	t_vec3		tangent;
	float		radius;
	float		height;
	t_vec3		extents;
	int			mat_id;
}	t_prim_params;

/**
 * @brief Unified Primitive Array in SoA (Structure of Arrays) layout.
 * Optimized with float precision for maximum SIMD throughput.
 */
typedef struct s_primitive_array
{
	uint8_t		*types;      /* 1 byte per primitive: e_prim_type */
	float		*px;         /* Position component X */
	float		*py;         /* Position component Y */
	float		*pz;         /* Position component Z */
	float		*ax;         /* Normal/Axis component X (primary axis) */
	float		*ay;         /* Normal/Axis component Y (primary axis) */
	float		*az;         /* Normal/Axis component Z (primary axis) */
	float		*tx;         /* Tangent component X (local basis orientation) */
	float		*ty;         /* Tangent component Y (local basis orientation) */
	float		*tz;         /* Tangent component Z (local basis orientation) */
	float		*radii;      /* Sphere/Cyl/Capsule radii */
	float		*heights;    /* Cyl/Capsule/Pyramid full heights */
	float		*ex;         /* Extent X: half-width for Box/Rect/Pyramid */
	float		*ey;         /* Extent Y: half-height for Box/Rect */
	float		*ez;         /* Extent Z: half-depth for Box/Rect/Pyramid */
	uint16_t	*mat_ids;    /* Material pool indices */
	struct s_physics_body **physics; /* Pointers to physics controllers */
	size_t		count;       /* Active primitive count */
	size_t		capacity;    /* Allocated capacity */
}	t_primitive_array;

/**
 * @brief Structure of Arrays (SoA) for Triangles.
 * Uses float precision and parallel components for AVX/SSE batch processing.
 * Includes pre-computed world-space normals and tangents.
 */
typedef struct s_tri_array
{
	float		*vx[3];
	float		*vy[3];
	float		*vz[3];
	float		*ex[2];
	float		*ey[2];
	float		*ez[2];
	float		*nx;    /* Face normal components */
	float		*ny;
	float		*nz;
	float		*tx;    /* Surface tangent components */
	float		*ty;
	float		*tz;
	uint16_t	*mat_ids;
	size_t		count;
	size_t		cap;
}	t_tri_array;

/* Intermediate mesh structure used during loading phase */
typedef struct s_mesh
{
	t_vec3		*vertices;
	size_t		vertex_count;
	int			*indices;
	size_t		tri_count;
	t_vec2		*uvs;
	t_vec3		*normals;
	int			mat_id;
	t_transform	transform;
}	t_mesh;

#endif

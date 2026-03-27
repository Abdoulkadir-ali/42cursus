/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 02:45:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdint.h>
# include <stddef.h>
# include "math_mini.h"
# include "material.h"

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
	PRIM_CAPSULE
}	t_prim_type;

/**
 * @brief Unified Primitive Array in SoA (Structure of Arrays) layout.
 * Optimized for massive scenes with size_t capacities.
 */
typedef struct s_primitive_array
{
	uint8_t		*types;      /* 1 byte per primitive */
	t_vec3		*positions;  /* World-space positions */
	t_vec3		*axes;       /* Shared axis/normals */
	float		*radii;      /* For spheres, cylinders, cones, capsules */
	float		*heights;    /* For cylinders, cones, pyramids */
	uint16_t	*mat_ids;    /* Memory-efficient material mapping */
	size_t		count;
	size_t		capacity;
}	t_primitive_array;

/**
 * @brief Structure of Arrays (SoA) for Triangles.
 * Now includes pre-computed tangents for branchless bump mapping.
 */
typedef struct s_tri_array
{
	double		*vx[3];
	double		*vy[3];
	double		*vz[3];
	double		*ex[2];
	double		*ey[2];
	double		*ez[2];
	double		*nx;    /* Pre-computed face normals */
	double		*ny;
	double		*nz;
	double		*tx;    /* Pre-computed world-space tangents */
	double		*ty;
	double		*tz;
	uint16_t	*mat_ids;
	size_t		count;
	size_t		cap;
}	t_tri_array;

/* Mesh data kept for intermediate processing before SoA flattening */
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

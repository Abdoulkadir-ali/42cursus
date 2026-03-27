/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 04:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "objects.h"

/**
 * @brief Unified DOD AABB queries for the primitive SoA.
 * Centralizes all bounding box calculations to prevent code duplication.
 * Optimized with float precision for SIMD readiness.
 */
t_aabb	get_primitive_aabb_soa(t_primitive_array *p, int i);
t_aabb	get_tri_aabb_soa(t_tri_array *t, int i);

/* --- FAST AABB PRIMITIVES --- */
t_aabb	sphere_aabb_f(float px, float py, float pz, float r);
t_aabb	plane_aabb_f(float px, float py, float pz, float ax, float ay, float az);
t_aabb	box_aabb_f(float px, float py, float pz, float ax, float ay, float az, float r);
t_aabb	tri_aabb_f(float v0[3], float v1[3], float v2[3]);

#endif

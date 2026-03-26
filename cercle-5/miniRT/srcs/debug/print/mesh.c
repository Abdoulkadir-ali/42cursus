/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/10 12:49:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"
#include "debug.h"

void	debug_print_mesh_hit(const t_ray *ray, int tri_idx, double t)
{
	printf("DEBUG: Mesh Triangle HIT: idx=%d, t=%f, ", tri_idx, t);
	printf("ray_org=(%f, %f, %f)\n", ray->origin.x, ray->origin.y,
		ray->origin.z);
}

void	debug_print_mesh_aabb(const t_ray *ray, double tmin, double tmax)
{
	printf("DEBUG: Mesh Root AABB HIT: tmin=%.2f, tmax=%.2f, ",
		tmin, tmax);
	printf("org=(%.1f,%.1f,%.1f), ", ray->origin.x, ray->origin.y,
		ray->origin.z);
	printf("dir=(%.2f,%.2f,%.2f)\n", ray->direction.x, ray->direction.y,
		ray->direction.z);
}

void	debug_print_bvh_build(int tri_count, int depth, bool start)
{
	(void)tri_count;
	(void)depth;
	(void)start;
}

void	debug_print_mesh_bake(const t_mesh *mesh, bool start)
{
	(void)mesh;
	(void)start;
}

void	debug_print_triangle_test(int tri_idx, const t_vec3 *v)
{
	(void)v;
	printf("DEBUG: Testing triangle %d\n", tri_idx);
}

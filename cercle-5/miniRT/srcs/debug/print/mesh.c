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

#include "debug.h"
#include "maths.h"
#include "objects.h"

void	debug_print_mesh_hit(const t_ray *ray, int tri_idx, double t)
{
	printf("DEBUG: Mesh Triangle HIT: idx=%d, t=%f, ray_org=(%f, %f, %f)\n", \
		tri_idx, t, ray->origin.x, ray->origin.y, ray->origin.z);
}

void	debug_print_mesh_aabb(const t_ray *ray, double tmin, double tmax)
{
	printf("DEBUG: Mesh Root AABB HIT: tmin=%.2f, tmax=%.2f, org=(%.1f,%.1f,%.1f), dir=(%.2f,%.2f,%.2f)\n", \
		tmin, tmax, ray->origin.x, ray->origin.y, ray->origin.z, \
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	debug_print_bvh_build(int tri_count, int depth, bool start)
{
	if (start)
		printf("DEBUG: Starting BVH build for %d triangles...\n", tri_count);
	else
		printf("DEBUG: BVH Build depth %d: Finished processing %d items\n", depth, tri_count);
	fflush(stdout);
}

void	debug_print_mesh_bake(const t_mesh *mesh, bool start)
{
	if (start)
		printf("DEBUG: Starting Mesh bake for '%s'...\n", mesh->name ? mesh->name : "OBJ");
	else
		printf("DEBUG: Mesh '%s' bake complete (%d vertices transformed)\n", \
			mesh->name ? mesh->name : "OBJ", mesh->vertex_count);
	fflush(stdout);
}

void	debug_print_triangle_test(int tri_idx, const t_vec3 *v)
{
	(void)v;
	printf("DEBUG: Testing triangle %d\n", tri_idx);
}

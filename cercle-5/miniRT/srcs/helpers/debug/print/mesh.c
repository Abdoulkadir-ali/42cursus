/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (start)
		printf("DEBUG: Starting BVH build: tri_count=%d\n", tri_count);
	else
		printf("DEBUG: Finished BVH build: depth=%d\n", depth);
}

void	debug_print_mesh_bake(const t_mesh *mesh, bool start)
{
	if (start)
		printf("DEBUG: Starting mesh bake: %s\n", mesh->name ? mesh->name : "unnamed");
	else
		printf("DEBUG: Finished mesh bake\n");
}

void	debug_print_triangle_test(int tri_idx, const t_vec3 *v)
{
	printf("DEBUG: Testing triangle %d: v0=(%.2f,%.2f,%.2f)\n",
		tri_idx, v[0].x, v[0].y, v[0].z);
}

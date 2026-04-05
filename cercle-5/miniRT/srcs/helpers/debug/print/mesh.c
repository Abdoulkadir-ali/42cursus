/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 12:49:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	debug_print_mesh_hit(const t_ray *ray, int tri_idx, double t)
{
	ft_print_debug("DEBUG: Mesh Triangle HIT: idx=%d, t=%f, ", tri_idx, t);
	ft_print_debug("ray_org=(%f, %f, %f)\n", ray->origin.x, ray->origin.y,
		ray->origin.z);
}

void	debug_print_mesh_aabb(const t_ray *ray, double tmin, double tmax)
{
	ft_print_debug("DEBUG: Mesh Root AABB HIT: tmin=%.2f, tmax=%.2f, ",
		tmin, tmax);
	ft_print_debug("org=(%.1f,%.1f,%.1f), ", ray->origin.x, ray->origin.y,
		ray->origin.z);
	ft_print_debug("dir=(%.2f,%.2f,%.2f)\n", ray->direction.x, ray->direction.y,
		ray->direction.z);
}

void	debug_print_bvh_build(size_t tri_count, size_t depth, bool start)
{
	if (start)
		ft_print_debug("DEBUG: Starting BVH build: tri_count=%zu\n", tri_count);
	else
		ft_print_debug("DEBUG: Finished BVH build: depth=%zu\n", depth);
}

void	debug_print_mesh_bake(const t_mesh *mesh, bool start)
{
	if (!start)
	{
		ft_print_debug("DEBUG: Finished mesh bake\n");
		return ;
	}
	if (mesh->name)
		ft_print_debug("DEBUG: Starting mesh bake: %s\n", mesh->name);
	else
		ft_print_debug("DEBUG: Starting mesh bake: unnamed\n");
}

void	debug_print_triangle_test(int tri_idx, const t_vec3 *v)
{
	ft_print_debug("DEBUG: Testing triangle %d: v0=(%.2f,%.2f,%.2f)\n",
		tri_idx, v[0].x, v[0].y, v[0].z);
}

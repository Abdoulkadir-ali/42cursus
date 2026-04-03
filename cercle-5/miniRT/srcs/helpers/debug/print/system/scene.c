/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_scene(t_scene *s)
{
	const char	*name;

	if (!s)
		return ;
	name = "NULL";
	if (s->name)
		name = s->name;
	printf("scene(\n  name: %s\n", name);
	printf("  counts: spheres: %zu, planes: %zu, ",
		s->sphere_count, s->plane_count);
	printf("cylinders: %zu, cones: %zu, meshes: %zu,\n",
		s->cylinder_count, s->cone_count, s->mesh_count);
	printf("          animated: %zu, lights: %zu, materials: %zu\n",
		s->anim_count, s->light_count, s->mat_count);
	printf("  ambient: ");
	print_ambient(&s->ambient);
	printf("\n  camera: ");
	print_camera(&s->camera);
	printf("\n)");
}

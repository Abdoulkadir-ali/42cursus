/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
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
	ft_print_debug("scene(\n  name: %s\n", name);
	ft_print_debug("  counts: spheres: %zu, planes: %zu, ",
		s->sphere_count, s->plane_count);
	ft_print_debug("cylinders: %zu, cones: %zu, meshes: %zu,\n",
		s->cylinder_count, s->cone_count, s->mesh_count);
	ft_print_debug("          animated: %zu, lights: %zu, materials: %zu\n",
		s->anim_count, s->light_count, s->mat_count);
	ft_print_debug("  ambient: ");
	print_ambient(&s->ambient);
	ft_print_debug("\n  camera: ");
	print_camera(&s->camera);
	ft_print_debug("\n)");
}

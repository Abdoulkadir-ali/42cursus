/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "debug.h"

void	print_ambient(t_ambient *a);
void	print_camera(t_camera *c);

void	print_scene(t_scene *s)
{
	const char	*name;

	if (!s)
		return ;
	name = "NULL";
	if (s->name)
		name = s->name;
	printf("scene(\n  name: %s\n", name);
	printf("  primitives: %zu  tris: %zu\n",
		s->primitives.count, s->tri_soa.count);
	printf("          animated: %zu, lights: %zu, materials: %zu\n",
		s->anim_count, s->light_count, s->mat_count);
	printf("  ambient: ");
	print_ambient(&s->ambient);
	printf("\n  camera: ");
	print_camera(&s->camera);
	printf("\n)");
}

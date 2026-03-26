/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"
#include "debug.h"

static void	print_texture(t_texture *t, const char *name)
{
	static const char	*types[] = {"SOLID", "CHECKER", "BITMAP", "BUMP"};

	if (!t)
		return ;
	printf("    %s: type: %s, color_a: ", name, types[t->type]);
	print_vec3(&t->color_a);
	printf(", color_b: ");
	print_vec3(&t->color_b);
	printf(", scale: %.4f\n", t->scale);
}

void	print_material(t_material *m)
{
	if (!m)
		return ;
	printf("material(\n");
	print_texture(&m->albedo_map, "albedo_map");
	print_texture(&m->bump_map, "bump_map");
	printf("    specular: %.4f, shininess: %.4f\n",
		m->specular, m->shininess);
	printf("    metallic: %.4f, roughness: %.4f\n",
		m->metallic, m->roughness);
	printf("    emission: ");
	print_vec3(&m->emission);
	printf("\n    refract_index: %.4f, ", m->refract_index);
	printf("transparency: %.4f, reflectivity: %.4f\n)",
		m->transparency, m->reflectivity);
}

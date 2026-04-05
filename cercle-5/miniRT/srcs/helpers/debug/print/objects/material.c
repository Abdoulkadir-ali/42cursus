/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

static void	print_texture(t_texture *t, const char *name)
{
	static const char	*types[] = {"SOLID", "CHECKER", "BITMAP", "BUMP"};

	if (!t)
		return ;
	ft_print_debug("    %s: type: %s, color_a: ", name, types[t->type]);
	print_vec3(&t->color_a);
	ft_print_debug(", color_b: ");
	print_vec3(&t->color_b);
	ft_print_debug(", scale: %.4f\n", t->scale);
}

void	print_material(t_material *m)
{
	if (!m)
		return ;
	ft_print_debug("material(\n");
	print_texture(&m->albedo_map, "albedo_map");
	print_texture(&m->bump_map, "bump_map");
	ft_print_debug("    specular: %.4f, shininess: %.4f\n",
		m->specular, m->shininess);
	ft_print_debug("    metallic: %.4f, roughness: %.4f\n",
		m->metallic, m->roughness);
	ft_print_debug("    emission: ");
	print_vec3(&m->emission);
	ft_print_debug("\n    refract_index: %.4f, ", m->refract_index);
	ft_print_debug("transparency: %.4f, reflectivity: %.4f\n)",
		m->transparency, m->reflectivity);
}

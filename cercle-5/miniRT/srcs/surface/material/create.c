/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 13:42:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "surface.h"

t_material	*create_material(t_material_params params)
{
	t_material	*mat;

	mat = malloc(sizeof(t_material));
	if (!mat)
		return (NULL);
	ft_memset(mat, 0, sizeof(t_material));
	mat->albedo_map.type = TEX_SOLID;
	mat->albedo_map.color_a = params.albedo;
	mat->albedo_map.scale = 1.0;
	mat->metallic = params.metallic;
	mat->roughness = params.roughness;
	mat->emission = params.emission;
	mat->refract_index = params.refract_index;
	mat->transparency = params.transparency;
	mat->reflectivity = params.reflectivity;
	mat->specular = 0.5;
	mat->shininess = 32.0;
	return (mat);
}

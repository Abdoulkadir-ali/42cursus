/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 09:16:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	model_apply_transform(t_raw_model *model, t_transform transform)
{
	int	i;

	i = 0;
	while (i < model->mesh_count)
	{
		model->meshes[i].transform = transform;
		mesh_apply_transform(&model->meshes[i], transform);
		i++;
	}
}

void	model_apply_material_override(t_raw_model *model, t_vec3 color, t_vec3 emission)
{
	int		idx;
	bool	has_override;

	has_override = (color.x != 255.0 || color.y != 255.0 || color.z != 255.0);
	if (!has_override)
		return ;
	idx = 0;
	while (idx < model->mat_count)
	{
		model->materials[idx].color = color;
		model->materials[idx].emission = emission;
		idx++;
	}
}

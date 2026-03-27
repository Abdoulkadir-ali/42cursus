/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 21:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:11:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"
#include "surface.h"

int	raw_model_add_material(t_raw_model *model, const char *name)
{
    int	idx;

    if (!dynarray_ensure((void **)&model->materials, model->mat_count + 1, NULL, sizeof(t_raw_material)))
        return (-1);
    idx = model->mat_count++;
    ft_memset(&model->materials[idx], 0, sizeof(t_raw_material));
    if (name)
        ft_strlcpy(model->materials[idx].name, name, 64);
    else
        ft_strlcpy(model->materials[idx].name, "RawMaterial", 64);
    model->materials[idx].color = get_colors()->white;
    return (idx);
}

void	raw_material_set_texture(t_raw_material *mat, const char *path)
{
    if (!mat || !path)
        return ;
    ft_strlcpy(mat->albedo_map_path, path, 256);
    mat->has_tex = true;
}

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
#include "debug.h"

 t_material	*create_material(void)
{
    t_material	*mat;

    DBG_TRACE_MSG(DBG_CH_PARSER, "create_material: entry\n");
    mat = malloc(sizeof(t_material));
    if (!mat)
    {
        DBG_ERR_MSG(DBG_CH_PARSER, "create_material: malloc failed\n");
        return (NULL);
    }
    ft_memset(mat, 0, sizeof(t_material));
    mat->albedo_map.type = TEX_SOLID;
    mat->albedo_map.color_a = get_colors()->white;
    mat->albedo_map.scale = 1.0;
    mat->metallic = 0.0;
    mat->roughness = 1.0;
    mat->emission = get_colors()->black;
    mat->refract_index = 1.0;
    mat->transparency = 0.0;
    mat->reflectivity = 0.0;
    mat->specular = 0.5;
    mat->shininess = 32.0;
    DBG_INFO_MSG(DBG_CH_PARSER, "create_material: OK\n");
    return (mat);
}

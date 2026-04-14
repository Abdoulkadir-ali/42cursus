/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 10:40:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	build_mat_emissive_sliders(t_material *mat, t_islider *sl,
	int *i)
{
	sl[(*i)++] = (t_islider){"Emission R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x, sync_group_materials};
	sl[(*i)++] = (t_islider){"Emission G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y, sync_group_materials};
	sl[(*i)++] = (t_islider){"Emission B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z, sync_group_materials};
	sl[(*i)++] = (t_islider){"Em.Power", SL_EM_POWER_MIN, SL_EM_POWER_MAX,
		&mat->em_intensity, sync_group_materials};
}

void	build_mat_sliders(t_material *mat, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness, sync_group_materials};
	sl[i++] = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic, sync_group_materials};
	sl[i++] = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency, sync_group_materials};
	sl[i++] = (t_islider){"Reflectivity", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity, sync_group_materials};
	sl[i++] = (t_islider){"Refr.Angle", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index, sync_group_materials};
	sl[i++] = (t_islider){"Albedo R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x, sync_group_materials};
	sl[i++] = (t_islider){"Albedo G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y, sync_group_materials};
	sl[i++] = (t_islider){"Albedo B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z, sync_group_materials};
	build_mat_emissive_sliders(mat, sl, &i);
	*count = i;
}

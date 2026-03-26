/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sliders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:50:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
void	build_mat_sliders(t_material *mat, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness};
	sl[i++] = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic};
	sl[i++] = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency};
	sl[i++] = (t_islider){"Reflectivity", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity};
	sl[i++] = (t_islider){"Refr.Angle", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index};
	sl[i++] = (t_islider){"Albedo R", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.x};
	sl[i++] = (t_islider){"Albedo G", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.y};
	sl[i++] = (t_islider){"Albedo B", SL_COL_MIN, SL_COL_MAX,
		&mat->albedo_map.color_a.z};
	sl[i++] = (t_islider){"Emission R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x};
	sl[i++] = (t_islider){"Emission G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y};
	sl[i++] = (t_islider){"Emission B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z};
	*count = i;
}

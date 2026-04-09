/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surface.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	set_surf_sl(t_material *mat, t_islider sl[6])
{
	sl[0] = (t_islider){"Roughness", SL_ROUGH_MIN, SL_ROUGH_MAX,
		&mat->roughness, sync_group_materials};
	sl[1] = (t_islider){"Metallic", SL_METAL_MIN, SL_METAL_MAX,
		&mat->metallic, sync_group_materials};
	sl[2] = (t_islider){"Opacity", SL_OPAC_MIN, SL_OPAC_MAX,
		&mat->transparency, sync_group_materials};
	sl[3] = (t_islider){"Reflect", SL_REFL_MIN, SL_REFL_MAX,
		&mat->reflectivity, sync_group_materials};
	sl[4] = (t_islider){"IOR", SL_IOR_MIN, SL_IOR_MAX,
		&mat->refract_index, sync_group_materials};
	sl[5] = (t_islider){"Shininess", SL_SHINE_MIN, SL_SHINE_MAX,
		&mat->shininess, sync_group_materials};
}

bool	click_mat_surface(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl[6];
	size_t		i;

	d = gui->win.disp_size;
	set_surf_sl(mat, sl);
	p->y += ui_sy(INSP_HDR_STEP, d);
	i = 0;
	while (i < 6)
	{
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

bool	click_mat_emission(t_gui *gui, t_vec2i mouse, t_material *mat,
		t_vec2i *p)
{
	t_vec2s		d;
	t_islider	sl[4];
	size_t		i;

	d = gui->win.disp_size;
	sl[0] = (t_islider){"R", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.x, sync_group_materials};
	sl[1] = (t_islider){"G", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.y, sync_group_materials};
	sl[2] = (t_islider){"B", SL_EMIT_MIN, SL_EMIT_MAX,
		&mat->emission.z, sync_group_materials};
	sl[3] = (t_islider){"Power", SL_EM_POWER_MIN, SL_EM_POWER_MAX,
		&mat->em_intensity, sync_group_materials};
	p->y += ui_sy(6 + INSP_HDR_STEP, d);
	i = 0;
	while (i < 4)
	{
		if (insp_row_click(gui, mouse, (t_vec2i){p->x, p->y}, sl[i]))
			return (true);
		p->y += ui_sy(INSP_ROW_STEP, d);
		i++;
	}
	return (false);
}

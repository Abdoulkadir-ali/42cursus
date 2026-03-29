/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/28 17:22:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
void	draw_vec3_label(t_gui *gui, const t_vec3_label_arg *a)
{
    char	buf[80];

    snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", a->v.x, a->v.y, a->v.z);
    gui_draw_string(gui, (char *)a->label, a->pos.x + 8, a->pos.y, COL_HOVER);
    gui_draw_string(gui, buf, a->pos.x + 8, a->pos.y + 14, COL_TEXT);
}

void	draw_bool_label(t_gui *gui, const t_bool_label_arg *a)
{
    char	buf[32];

    if (a->val)
        snprintf(buf, sizeof(buf), "%s [YES]", a->label);
    else
        snprintf(buf, sizeof(buf), "%s [NO]", a->label);
    gui_draw_string(gui, buf, a->pos.x + 8, a->pos.y, COL_TEXT);
}

void	build_phys_sliders(t_physics_body *phys, t_islider out[3])
{
	int	i;

	(void)phys;
	i = 0;
	while (g_props_physics[i])
	{
		out[i] = (t_islider){g_props_physics[i]->name, g_props_physics[i]->min,
			g_props_physics[i]->max, NULL, g_props_physics[i]};
		i++;
	}
}

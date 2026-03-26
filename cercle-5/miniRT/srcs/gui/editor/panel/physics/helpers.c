/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:34:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "gui.h"

static void	draw_vec3_label(t_gui *gui, const t_vec3_label_arg *a)
{
    char	buf[80];

    snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f", a->v.x, a->v.y, a->v.z);
    mlx_string_put(gui->win.mlx, gui->win.win, a->x + 8, a->y, COL_HOVER,
        (char *)a->label);
    mlx_string_put(gui->win.mlx, gui->win.win, a->x + 8, a->y + 14, COL_TEXT,
        buf);
}

static void	draw_bool_label(t_gui *gui, const t_bool_label_arg *a)
{
    char	buf[32];

    if (a->val)
        snprintf(buf, sizeof(buf), "%s [YES]", a->label);
    else
        snprintf(buf, sizeof(buf), "%s [NO]", a->label);
    mlx_string_put(gui->win.mlx, gui->win.win, a->x + 8, a->y, COL_TEXT, buf);
}

void	build_phys_sliders(t_physics_body *phys, t_islider out[3])
{
    out[0] = (t_islider){"Mass (kg)", SL_MASS_MIN, SL_MASS_MAX, &phys->mass};
    out[1] = (t_islider){"Elasticity", SL_ELAST_MIN, SL_ELAST_MAX,
        &phys->elasticity};
    out[2] = (t_islider){"Friction", SL_FRIC_MIN, SL_FRIC_MAX, &phys->friction};
}

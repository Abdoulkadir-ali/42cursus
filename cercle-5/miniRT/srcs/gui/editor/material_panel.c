/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 20:54:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	draw_mat_double(t_gui *gui, int x, int *y,
	const char *label, double value)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "%s %.3f", label, value);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, *y, COL_TEXT, buf);
	*y += 20;
}

static void	draw_mat_color(t_gui *gui, int x, int *y,
	const char *label, t_vec3 c)
{
	char	buf[64];

	snprintf(buf, sizeof(buf), "%s %.2f %.2f %.2f",
		label, c.x, c.y, c.z);
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, *y, COL_TEXT, buf);
	*y += 20;
}

void	draw_material_panel_text(t_gui *gui, int x)
{
	t_material	*mat;
	int			y;

	mat = get_selected_material(gui);
	if (!mat)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			x + 8, 90, COL_TEXT, "No material");
		return ;
	}
	y = 90;
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, y, COL_HOVER,
		"Material");
	y += 22;
	draw_mat_color(gui, x, &y, "Albedo :", mat->albedo_map.color_a);
	draw_mat_double(gui, x, &y, "Roughness  :", mat->roughness);
	draw_mat_double(gui, x, &y, "Metallic   :", mat->metallic);
	draw_mat_double(gui, x, &y, "Opacity    :", mat->transparency);
	draw_mat_double(gui, x, &y, "Reflect    :", mat->reflectivity);
	draw_mat_double(gui, x, &y, "IOR        :", mat->refract_index);
	draw_mat_color(gui, x, &y, "Emission :", mat->emission);
}

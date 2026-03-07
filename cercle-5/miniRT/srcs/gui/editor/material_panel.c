/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_panel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 21:44:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	build_mat_sliders(t_material *mat, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Roughness", 0.0, 1.0, &mat->roughness};
	sl[i++] = (t_islider){"Metallic", 0.0, 1.0, &mat->metallic};
	sl[i++] = (t_islider){"Opacity", 0.0, 1.0, &mat->transparency};
	sl[i++] = (t_islider){"Reflectivity", 0.0, 1.0, &mat->reflectivity};
	sl[i++] = (t_islider){"IOR", 1.0, 3.0, &mat->refract_index};
	sl[i++] = (t_islider){"Albedo R", 0.0, 1.0, &mat->albedo_map.color_a.x};
	sl[i++] = (t_islider){"Albedo G", 0.0, 1.0, &mat->albedo_map.color_a.y};
	sl[i++] = (t_islider){"Albedo B", 0.0, 1.0, &mat->albedo_map.color_a.z};
	sl[i++] = (t_islider){"Emission R", 0.0, 10.0, &mat->emission.x};
	sl[i++] = (t_islider){"Emission G", 0.0, 10.0, &mat->emission.y};
	sl[i++] = (t_islider){"Emission B", 0.0, 10.0, &mat->emission.z};
	*count = i;
}

void	draw_material_panel_text(t_gui *gui, int x)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;

	mat = get_selected_material(gui);
	if (!mat)
	{
		mlx_string_put(gui->win.mlx, gui->win.win,
			x + 8, 90, COL_TEXT, "No material");
		return ;
	}
	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 88, COL_HOVER, "MATERIAL");
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, vec2i(x + 8, y), sl[i]);
		y += 30;
		i++;
	}
}

bool	material_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_material	*mat;
	t_islider	sl[11];
	int			count;
	int			i;
	int			y;
	int			x;

	mat = get_selected_material(gui);
	if (!mat)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	build_mat_sliders(mat, sl, &count);
	y = 104;
	i = 0;
	while (i < count)
	{
		if (try_islider_click(gui, mouse, vec2i(x + 8, y), sl[i]))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}

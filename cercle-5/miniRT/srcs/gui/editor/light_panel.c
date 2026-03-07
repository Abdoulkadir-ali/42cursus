/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_panel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/07 23:11:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "editor.h"

static void	build_light_sliders(t_light *lt, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Intensity", 0.0, 5.0, &lt->brightness};
	sl[i++] = (t_islider){"Color R", 0.0, 1.0, &lt->rgb.x};
	sl[i++] = (t_islider){"Color G", 0.0, 1.0, &lt->rgb.y};
	sl[i++] = (t_islider){"Color B", 0.0, 1.0, &lt->rgb.z};
	if (lt->type == LIGHT_SPOT)
		sl[i++] = (t_islider){"Cutoff (deg)", 0.0, 90.0, &lt->cutoff};
	*count = i;
}

void	draw_light_panel(t_gui *gui, int x)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	int			y;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return ;
	lt = &gui->scene->lights[gui->selection.index];
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER, "LIGHT");
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 100, COL_TEXT,
		lt->type == LIGHT_SPOT ? "Type: Spot" : "Type: Point");
	build_light_sliders(lt, sl, &count);
	y = 116;
	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, vec2i(x + 8, y), sl[i]);
		y += 30;
		i++;
	}
}

bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	int			i;
	int			y;
	int			x;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return (false);
	lt = &gui->scene->lights[gui->selection.index];
	x = gui->win.disp_w - gui->inspector.width;
	build_light_sliders(lt, sl, &count);
	y = 116;
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

void	draw_ambient_panel(t_gui *gui, int x)
{
	t_islider	sl[4];
	int			i;
	int			y;

	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 88, COL_HOVER, "AMBIENT LIGHT");
	sl[0] = (t_islider){"Intensity", 0.0, 2.0, &gui->scene->ambient.brightness};
	sl[1] = (t_islider){"Color R", 0.0, 1.0, &gui->scene->ambient.rgb.x};
	sl[2] = (t_islider){"Color G", 0.0, 1.0, &gui->scene->ambient.rgb.y};
	sl[3] = (t_islider){"Color B", 0.0, 1.0, &gui->scene->ambient.rgb.z};
	y = 104;
	i = 0;
	while (i < 4)
	{
		draw_slider_row(gui, vec2i(x + 8, y), sl[i]);
		y += 30;
		i++;
	}
}

bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_islider	sl[4];
	int			i;
	int			y;
	int			x;

	if (!gui->scene)
		return (false);
	x = gui->win.disp_w - gui->inspector.width;
	sl[0] = (t_islider){"Intensity", 0.0, 2.0, &gui->scene->ambient.brightness};
	sl[1] = (t_islider){"Color R", 0.0, 1.0, &gui->scene->ambient.rgb.x};
	sl[2] = (t_islider){"Color G", 0.0, 1.0, &gui->scene->ambient.rgb.y};
	sl[3] = (t_islider){"Color B", 0.0, 1.0, &gui->scene->ambient.rgb.z};
	y = 104;
	i = 0;
	while (i < 4)
	{
		if (try_islider_click(gui, mouse, vec2i(x + 8, y), sl[i]))
			return (true);
		y += 30;
		i++;
	}
	return (false);
}

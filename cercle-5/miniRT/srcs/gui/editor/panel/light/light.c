/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 21:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 20:00:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_light_panel(t_gui *gui, int x)
{
	t_light		*lt;
	t_islider	sl[5];
	int			count;
	char		*type;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return ;
	lt = &gui->scene->lights[gui->selection.index];
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER, "LIGHT");
	type = "Type: Point";
	if (lt->type == LIGHT_SPOT)
		type = "Type: Spot";
	mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 100, COL_TEXT, type);
	build_light_sliders(lt, sl, &count);
	draw_panel_sliders(gui, sl, count, (t_vec2i){x + 8, 116});
}

bool	light_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_light		*lt;
	t_islider	sl[5];
	t_vec2i		p;
	int			count;
	int			i;

	if (!gui->scene || gui->selection.index >= gui->scene->light_count)
		return (false);
	lt = &gui->scene->lights[gui->selection.index];
	p.x = gui->win.disp_w - gui->inspector.width + 8;
	p.y = 116;
	build_light_sliders(lt, sl, &count);
	i = 0;
	while (i < count)
	{
		if (try_islider_click(gui, mouse, p, sl[i], NULL))
			return (true);
		p.y += 30;
		i++;
	}
	return (false);
}

void	draw_ambient_panel(t_gui *gui, int x)
{
	t_islider	sl[4];

	mlx_string_put(gui->win.mlx, gui->win.win,
		x + 8, 88, COL_HOVER, "AMBIENT LIGHT");
	get_ambient_sliders(gui->scene, sl);
	draw_panel_sliders(gui, sl, 4, (t_vec2i){x + 8, 104});
}

bool	ambient_panel_handle_click(t_gui *gui, t_vec2i mouse)
{
	t_islider	sl[4];
	t_vec2i		p;
	int			i;

	if (!gui->scene)
		return (false);
	p.x = gui->win.disp_w - gui->inspector.width + 8;
	p.y = 104;
	get_ambient_sliders(gui->scene, sl);
	i = 0;
	while (i < 4)
	{
		if (try_islider_click(gui, mouse, p, sl[i], NULL))
			return (true);
		p.y += 30;
		i++;
	}
	return (false);
}

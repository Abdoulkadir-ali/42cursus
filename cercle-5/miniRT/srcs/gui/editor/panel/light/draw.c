/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 16:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 08:42:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
static void	build_light_sliders(t_light *lt, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Intensity", SL_INTENSITY_MIN, SL_INTENSITY_MAX,
		&lt->brightness};
	sl[i++] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX, &lt->rgb.x};
	sl[i++] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX, &lt->rgb.y};
	sl[i++] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX, &lt->rgb.z};
	if (lt->type == LIGHT_SPOT)
		sl[i++] = (t_islider){"Cutoff (deg)", SL_CUTOFF_MIN, SL_CUTOFF_MAX,
			&lt->cutoff};
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
		draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
		y += 30;
		i++;
	}
}


void	draw_ambient_panel(t_gui *gui, int x)
{
    t_islider	sl[4];
    int			i;
    int			y;

    mlx_string_put(gui->win.mlx, gui->win.win, x + 8, 88, COL_HOVER,
        "AMBIENT LIGHT");
    sl[0] = (t_islider){"Intensity", SL_AMB_MIN, SL_AMB_MAX,
        &gui->scene->ambient.brightness};
    sl[1] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.x};
    sl[2] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.y};
    sl[3] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX,
        &gui->scene->ambient.rgb.z};
    y = 104;
    i = 0;
    while (i < 4)
    {
        draw_slider_row(gui, (t_slider_arg){vec2i(x + 8, y), sl[i], NULL});
        y += 30;
        i++;
    }
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 15:17:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	build_light_sliders(t_light *lt, t_islider *sl, int *count)
{
	int	i;

	i = 0;
	sl[i++] = (t_islider){"Intensity", SL_INTENSITY_MIN, SL_INTENSITY_MAX,
		&lt->brightness, NULL};
	sl[i++] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX, &lt->rgb.x, NULL};
	sl[i++] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX, &lt->rgb.y, NULL};
	sl[i++] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX, &lt->rgb.z, NULL};
	if (lt->type == LIGHT_SPOT)
		sl[i++] = (t_islider){"Cutoff (deg)", SL_CUTOFF_MIN, SL_CUTOFF_MAX,
			&lt->cutoff, NULL};
	*count = i;
}

void	get_ambient_sliders(t_scene *scene, t_islider sl[4])
{
	sl[0] = (t_islider){"Intensity", SL_AMB_MIN, SL_AMB_MAX,
		&scene->ambient.brightness, NULL};
	sl[1] = (t_islider){"Color R", SL_COL_MIN, SL_COL_MAX,
		&scene->ambient.rgb.x, NULL};
	sl[2] = (t_islider){"Color G", SL_COL_MIN, SL_COL_MAX,
		&scene->ambient.rgb.y, NULL};
	sl[3] = (t_islider){"Color B", SL_COL_MIN, SL_COL_MAX,
		&scene->ambient.rgb.z, NULL};
}

void	draw_panel_sliders(t_gui *gui, t_islider *sl, int count, t_vec2i pos)
{
	int	i;

	i = 0;
	while (i < count)
	{
		draw_slider_row(gui, pos, sl[i]);
		pos.y += 30;
		i++;
	}
}

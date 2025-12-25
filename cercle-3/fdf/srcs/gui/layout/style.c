/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   style.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:45:55 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 22:08:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	draw_style_display(t_gui *gui)
{
	int		y;
	int		accent;
	char	*names[GUI_STYLE_COUNT];

	names[0] = "TRON BLUE";
	names[1] = "TRON ORANGE";
	names[2] = "MATRIX";
	names[3] = "CYBERPUNK";
	names[4] = "NEON GRID";
	y = gui->window->height - 240;
	accent = get_gui_theme(gui->gui_style).accent;
	put_colored(gui, GUI_PADDING, y, (t_colored_text){"GUI STYLE", accent});
	y += GUI_TITLE_HEIGHT;
	put_colored(gui, GUI_PADDING + 10, y,
		(t_colored_text){names[gui->gui_style], accent});
}

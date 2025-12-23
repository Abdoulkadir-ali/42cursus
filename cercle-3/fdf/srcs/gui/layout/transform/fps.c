/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 18:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:39:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_fps_stats(t_layout *l, t_gui *gui, char *buffer)
{
	format_number(gui->fps, buffer);
	gui_layout_key_value(l, "FPS:", buffer);
}

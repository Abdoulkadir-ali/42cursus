/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_bbox.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/08 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	draw_bbox_info(t_gui *gui, t_mesh *mesh, t_vec2i pos)
{
	t_vec2s	d;
	char	buf[64];
	int		y;

	d = gui->win.disp_size;
	y = ui_sy(106 + 18 * 4, d);
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.min.x, mesh->bbox.min.y, mesh->bbox.min.z);
	draw_info_row(gui, (t_vec2i){pos.x, y}, "BBox min:", buf);
	snprintf(buf, sizeof(buf), "%.2f  %.2f  %.2f",
		mesh->bbox.max.x, mesh->bbox.max.y, mesh->bbox.max.z);
	y += ui_sy(18, d);
	draw_info_row(gui, (t_vec2i){pos.x, y}, "BBox max:", buf);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 15:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "gui.h"

void	print_gui(t_gui *g)
{
	const char	*dirty;
	const char	*map_path;

	if (!g)
		return ;
	dirty = "false";
	if (g->render.dirty)
		dirty = "true";
	map_path = "none";
	if (g->map_info.current)
		map_path = g->map_info.current->path;
	printf("gui(\n  win: %dx%d\n", g->win.width, g->win.height);
	printf("  render: scale: %d, dirty: %s, fps: %.2f\n",
		g->render.scale, dirty, g->render.fps);
	printf("  map: %d maps, current: %s\n)",
		g->map_info.count, map_path);
}

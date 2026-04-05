/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

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
	ft_print_debug("gui(\n  win: %zux%zu\n", g->win.size.x, g->win.size.y);
	ft_print_debug("  render: scale: %zu, dirty: %s, fps: %.2f\n",
		g->render.scale, dirty, g->render.fps);
	ft_print_debug("  map: %zu maps, current: %s\n)",
		g->map_info.count, map_path);
}

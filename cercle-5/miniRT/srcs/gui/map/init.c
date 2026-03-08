/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	gui_map_switcher_init(t_gui *gui)
{
	gui->map_info.head = NULL;
	gui->map_info.current = NULL;
	gui->map_info.count = 0;
	fill_map_list(gui);
	if (gui->map_info.count == 0)
		return ;
	set_current_entry(gui);
}

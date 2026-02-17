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
	int	count;

	count = count_maps();
	if (count == 0)
		return ;
	gui->map_info.files = ft_calloc(count + 1, sizeof(char *));
	if (!gui->map_info.files)
		return ;
	fill_map_list(gui);
	set_current_index(gui);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	set_current_index(t_gui *gui)
{
	int	i;

	gui->map_info.current_idx = 0;
	if (gui->scene && gui->scene->name)
	{
		i = 0;
		while (i < gui->map_info.count)
		{
			if (ft_strcmp(gui->scene->name, gui->map_info.files[i]) == 0)
			{
				gui->map_info.current_idx = i;
				break ;
			}
			i++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:37:31 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 15:07:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_maps	init_maps(void)
{
	t_maps	m;

	m.maps = NULL;
	m.map_files = NULL;
	m.count = 0;
	m.current_index = 0;
	return (m);
}

t_map	*init_map(char *filename)
{
	t_map	*map;

	map = load_map(filename);
	if (map)
		apply_map_style(map);
	return (map);
}

t_map	*select_initial_map(t_maps *manager)
{
	init_map_list(manager);
	if (manager->count > 0)
	{
		manager->current_map = manager->maps[0];
		return (manager->current_map);
	}
	else
	{
		manager->current_map = create_test_grid();
		return (manager->current_map);
	}
}

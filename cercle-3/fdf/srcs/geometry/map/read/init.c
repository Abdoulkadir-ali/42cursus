/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/26 16:35:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 16:36:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

void	init_no_maps(t_maps *m)
{
	m->map_files = NULL;
	m->maps = NULL;
	m->count = 0;
	m->generated_id = 0;
}

void	allocate_maps(t_maps *m, size_t count)
{
	m->map_files = ft_calloc(count, sizeof(char *));
	m->maps = ft_calloc(count, sizeof(t_map *));
	m->count = count;
	m->generated_id = 0;
}

void	init_test_map(t_maps *m)
{
	m->current_map = create_test_grid();
	m->maps = malloc(sizeof(t_map *));
	m->maps[0] = m->current_map;
	m->map_files = NULL;
	m->count = 1;
	m->current_index = 0;
	m->generated_id = 0;
}

void	load_maps_from_dir(t_maps *m, char *dir_path, size_t count)
{
	DIR	*dir;

	allocate_maps(m, count);
	if (!m->maps || !m->map_files)
	{
		ft_printf("Allocation failed\n");
		return ;
	}
	dir = opendir(dir_path);
	load_map_files(m, dir, count, dir_path);
	closedir(dir);
	m->current_index = 0;
	m->current_map = m->maps[0];
	m->generated_id = 0;
	m->is_generating = 0;
}

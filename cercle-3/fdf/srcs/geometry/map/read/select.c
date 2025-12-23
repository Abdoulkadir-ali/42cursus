/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 17:44:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static void	init_no_maps(t_maps *m)
{
	m->map_files = NULL;
	m->maps = NULL;
	m->count = 0;
}

static void	allocate_maps(t_maps *m, size_t count)
{
	m->map_files = malloc(sizeof(char *) * count);
	m->maps = malloc(sizeof(t_map *) * count);
	m->count = count;
}

static void	init_test_map(t_maps *m)
{
	m->current_map = create_test_grid();
	m->maps = malloc(sizeof(t_map *));
	m->maps[0] = m->current_map;
	m->map_files = NULL;
	m->count = 1;
	m->current_index = 0;
}

void	init_map_list(t_maps *m)
{
	DIR		*dir;
	size_t	count;

	dir = opendir("maps/test_maps");
	if (!dir)
	{
		init_no_maps(m);
		return ;
	}
	count = count_fdf_files(dir);
	closedir(dir);
	if (count == 0)
	{
		init_test_map(m);
		return ;
	}
	allocate_maps(m, count);
	dir = opendir("maps/test_maps");
	load_map_files(m, dir, count);
	closedir(dir);
	m->current_index = 0;
	m->current_map = m->maps[0];
}

void	cycle_map(t_maps *m)
{
	if (!m->maps || m->count == 0)
		return ;
	m->current_index = (m->current_index + 1) % m->count;
	m->current_map = m->maps[m->current_index];
}

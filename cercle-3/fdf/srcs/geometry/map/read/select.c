/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 04:17:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

static void	init_no_maps(t_maps *m)
{
	m->map_files = NULL;
	m->maps = NULL;
	m->count = 0;
	m->generated_id = 0;
}

static void	allocate_maps(t_maps *m, size_t count)
{
	m->map_files = ft_calloc(count, sizeof(char *));
	m->maps = ft_calloc(count, sizeof(t_map *));
	m->count = count;
	m->generated_id = 0;
}

static void	init_test_map(t_maps *m)
{
	m->current_map = create_test_grid();
	m->maps = malloc(sizeof(t_map *));
	m->maps[0] = m->current_map;
	m->map_files = NULL;
	m->count = 1;
	m->current_index = 0;
	m->generated_id = 0;
}

void	init_map_list(t_maps *m, char *dir_path)
{
	DIR		*dir;
	size_t	count;

	dir = opendir(dir_path);
	if (!dir)
	{
		init_no_maps(m);
		return ;
	}
	count = count_fdf_files(dir);
	closedir(dir);
	if (count == 0)
		return (init_test_map(m));
	allocate_maps(m, count);
	dir = opendir(dir_path);
	load_map_files(m, dir, count, dir_path);
	closedir(dir);
	if (!m->maps || !m->maps[0])
		return (init_no_maps(m));
	m->current_index = 0;
	m->current_map = m->maps[0];
	m->generated_id = 0;
	m->is_generating = 0;
}

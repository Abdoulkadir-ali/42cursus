/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 16:36:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

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
	ft_printf("Found %d maps in %s\n", count, dir_path);
	if (count == 0)
	{
		init_test_map(m);
		return ;
	}
	load_maps_from_dir(m, dir_path, count);
}

void	cycle_map(t_maps *m)
{
	if (!m->maps || m->count == 0)
		return ;
	m->current_index = (m->current_index + 1) % m->count;
	m->current_map = m->maps[m->current_index];
}

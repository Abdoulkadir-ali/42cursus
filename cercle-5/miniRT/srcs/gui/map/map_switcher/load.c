/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

bool	load_scene_and_bvh(t_gui *gui, const char *path)
{
	t_scene	*new_s;
	t_bvh	*new_b;

	ft_print_debug("Switching to map: %s\n", path);
	new_s = parse_file(path, gui->win.mlx);
	if (!new_s)
	{
		fprintf(stderr, "Error: Failed to load map %s\n", path);
		return (false);
	}
	new_b = bvh_create(new_s);
	if (!new_b)
	{
		fprintf(stderr, "Error: Failed to create BVH for %s\n", path);
		destroy_scene(new_s);
		return (false);
	}
	bvh_destroy(gui->bvh);
	destroy_scene(gui->scene);
	gui->scene = new_s;
	gui->bvh = new_b;
	return (true);
}

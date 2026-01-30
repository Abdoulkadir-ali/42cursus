/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:20:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	main(int ac, char **av)
{
	const char	*path;
	t_scene		*scene;

	if (ac > 1)
		path = av[1];
	else
		path = "maps/test2.rt";
	scene = scene_load_from_file(path);
	if (!scene)
	{
		fprintf(stderr, "Failed to load scene: %s\n", path);
		return (1);
	}
	print_scene(scene);
	destroy_scene(scene);
	return (0);
}

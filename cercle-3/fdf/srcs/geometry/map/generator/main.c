/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:10:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

static t_gen_params	parse_args(int argc, char **argv, char **filename)
{
	t_gen_params	params;

	params.width = 50;
	params.height = 50;
	params.z_scale = 20.0;
	params.scale = 4.0;
	params.octaves = 4;
	params.persistence = 0.5;
	params.seed = time(NULL);
	*filename = "generated.fdf";
	if (argc > 1)
		*filename = argv[1];
	if (argc > 2)
		params.width = ft_atoi_safe(argv[2]);
	if (argc > 3)
		params.height = ft_atoi_safe(argv[3]);
	if (argc > 4)
		params.z_scale = ft_atof(argv[4]);
	if (argc > 5)
		params.scale = ft_atof(argv[5]);
	if (argc > 6)
		params.seed = ft_atoi_safe(argv[6]);
	return (params);
}

int	main(int argc, char **argv)
{
	t_gen_params	params;
	char			*filename;
	int				**map;

	params = parse_args(argc, argv, &filename);
	ft_printf("Generating map %dx%d (Scale: %.1f, Z: %.1f, Seed: %d)\n",
		params.width, params.height, params.scale, params.z_scale, params.seed);
	map = generate_heightmap(params);
	if (map)
	{
		save_map_to_file(map, params.width, params.height, filename);
		free_heightmap(map, params.height);
	}
	else
	{
		ft_printf("Error: Memory allocation failed.\n");
		return (1);
	}
	return (0);
}

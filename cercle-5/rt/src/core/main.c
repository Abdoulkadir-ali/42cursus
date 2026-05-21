/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:48:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	main(int argc, char **argv)
{
	int	bench_samples;

	bench_samples = 0;
	if (argc < 2 || argc > 4)
		return (usage());
	if (argc >= 3 && ft_strcmp(argv[1], "--bench") == 0)
		bench_samples = ft_atoi(argv[2]);
	return (mini_rt(argc, argv, bench_samples));
}

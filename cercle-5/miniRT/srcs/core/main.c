/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:14:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 05:15:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Entry point for the miniRT raytracer.
 * @param ac Argument count.
 * @param av Argument vector.
 * @return int Exit status.
 */
int	main(int ac, char **av)
{
	const char	*path;

	ft_putendl_fd("--- MINIRT STARTUP (v2026.03.26) ---", STDOUT_FILENO);
	setlocale(LC_NUMERIC, "C");
	path = "maps/rt/test2.rt";
	if (ac > 1)
		path = av[1];
	return (run_app(path));
}

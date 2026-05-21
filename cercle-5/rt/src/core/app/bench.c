/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:24:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:33:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	run_bench(t_app *app, int samples)
{
	double	start;
	double	end;

	printf("Benchmarking %d samples...\n", samples);
	start = time_ms_now();
	while (app->accum_samples < samples)
	{
		pool_run(&app->pool);
		app->accum_samples++;
	}
	end = time_ms_now();
	printf("Benchmark: %d samples in %.2f ms (%.2f ms/sample, %.2f FPS)\n",
		samples, end - start, (end - start) / samples, 1000.0f / ((end - start)
			/ samples));
}

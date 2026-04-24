/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/23 15:03:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "profiler.h"
#include "debug.h"

#ifdef PROFILE_MESH

t_profiler	g_profiler;

static void	prof_print_benchmark(int max_frames)
{
	double	avg;
	int		i;

	avg = 0;
	i = 2;
	while (i < g_profiler.frame_count)
	{
		avg += g_profiler.frame_times[i];
		i++;
	}
	if (g_profiler.frame_count > 2)
		avg /= (g_profiler.frame_count - 2);
	ft_print_debug("\n=== BENCHMARK (%d frames, skipped first 2) ===\n",
		max_frames);
	ft_print_debug("Avg frame: %.1f ms (%.1f FPS)\n", avg, 1000.0 / avg);
	fflush(stdout);
}

void	prof_print_frame(void)
{
	struct timespec	end;
	double			ms;
	int				max_frames;

	clock_gettime(CLOCK_MONOTONIC, &end);
	ms = (end.tv_sec - g_profiler.start.tv_sec) * 1000.0;
	ms += (end.tv_nsec - g_profiler.start.tv_nsec) / 1e6;
	fflush(stdout);
	if (g_profiler.frame_count < 1024)
		g_profiler.frame_times[g_profiler.frame_count++] = ms;
	g_profiler.frame++;
	max_frames = 20;
	if (getenv("BENCH_FRAMES"))
		max_frames = atoi(getenv("BENCH_FRAMES"));
	if (g_profiler.frame == max_frames)
	{
		prof_print_benchmark(max_frames);
#ifdef PROFILE_BUILD
		CALLGRIND_STOP_INSTRUMENTATION;
		CALLGRIND_DUMP_STATS;
#endif
	}
}

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:26:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "profiler.h"

#ifdef PROFILE_MESH

volatile long	g_mesh_calls = 0;
volatile long	g_mesh_aabb_tests = 0;
volatile long	g_mesh_tri_tests = 0;
volatile long	g_mesh_occ_calls = 0;
int				g_prof_frame = 0;
struct timespec	g_prof_start;
__thread long	tl_g_mesh_calls = 0;
__thread long	tl_g_mesh_aabb_tests = 0;
__thread long	tl_g_mesh_tri_tests = 0;
__thread long	tl_g_mesh_occ_calls = 0;

static double	g_frame_times[1024];
static int		g_frame_count = 0;

static void	prof_print_benchmark(int max_frames)
{
	double	avg;
	int		i;

	avg = 0;
	i = 2;
	while (i < g_frame_count)
	{
		avg += g_frame_times[i];
		i++;
	}
	if (g_frame_count > 2)
		avg /= (g_frame_count - 2);
	ft_print_debug("\n=== BENCHMARK (%d frames, skipped first 2) ===\n", max_frames);
	ft_print_debug("Avg frame: %.1f ms (%.1f FPS)\n", avg, 1000.0 / avg);
	fflush(stdout);
}

void	prof_print_frame(void)
{
	struct timespec	end;
	double			ms;
	int				max_frames;

	clock_gettime(CLOCK_MONOTONIC, &end);
	ms = (end.tv_sec - g_prof_start.tv_sec) * 1000.0;
	ms += (end.tv_nsec - g_prof_start.tv_nsec) / 1e6;
	fflush(stdout);
	if (g_frame_count < 1024)
		g_frame_times[g_frame_count++] = ms;
	g_prof_frame++;
	max_frames = 20;
	if (getenv("BENCH_FRAMES"))
		max_frames = atoi(getenv("BENCH_FRAMES"));
	if (g_prof_frame == max_frames)
		prof_print_benchmark(max_frames);
}

#endif

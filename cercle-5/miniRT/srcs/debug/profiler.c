/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 17:40:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef PROFILE_MESH

# include <stdio.h>
# include <stdlib.h>
# include <time.h>

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

void	prof_print_frame(void)
{
	struct timespec	end;
	double			ms;
	double			avg;
	int				i;
	int				max_frames;

	clock_gettime(CLOCK_MONOTONIC, &end);
	ms = (end.tv_sec - g_prof_start.tv_sec) * 1000.0
		+ (end.tv_nsec - g_prof_start.tv_nsec) / 1e6;
	printf("PROF[%d]: %.1fms (%.1f FPS) mesh=%ld aabb=%ld tri=%ld occ=%ld\n",
		g_prof_frame, ms, 1000.0 / ms,
		g_mesh_calls, g_mesh_aabb_tests, g_mesh_tri_tests, g_mesh_occ_calls);
	fflush(stdout);
	if (g_frame_count < 1024)
		g_frame_times[g_frame_count++] = ms;
	g_prof_frame++;
	max_frames = 20;
	if (getenv("BENCH_FRAMES"))
		max_frames = atoi(getenv("BENCH_FRAMES"));
	if (g_prof_frame == max_frames)
	{
		avg = 0;
		i = 2;
		while (i < g_frame_count)
		{
			avg += g_frame_times[i];
			i++;
		}
		if (g_frame_count > 2)
			avg /= (g_frame_count - 2);
		printf("\n=== BENCHMARK (%d frames, skipped first 2) ===\n", max_frames);
		printf("Avg frame: %.1f ms (%.1f FPS)\n", avg, 1000.0 / avg);
		fflush(stdout);
	}
}

#endif
